## Parse_tokens

### Introducción

parse_tokens convierte la lista lineal de tokens (ya expandidos y sin comillas) en una estructura semántica lista para ejecutar:

- comandos
- argumentos
- redirecciones
- pipelines

Es el puente entre el expander y el executor.

### Entrada

parse_tokens recibe:

```c
t_token *tokens;
```

Estos tokens ya han pasado por:

- Tokenizer
- Expander
- Quote removal

Por tanto, la entrada cumple:

- No hay comillas
- No hay $ sin expandir
- No hay tokens vacíos
- Los operadores están bien formados
- Los delimitadores de heredoc están intactos
- Los WORD son definitivos

##### Ejemplo de entrada:

```
WORD("ls")
WORD("-l")
PIPE("|")
WORD("grep")
WORD("txt")
REDIR_OUT(">")
WORD("out.txt")
```

##### Salida

Devuelve una lista enlazada de comandos:

```c
t_cmd *cmd_list;
Cada t_cmd contiene:
char **argv
t_redir *redirs
t_cmd *next
```

**Ejemplo:**

```bash
ls -l | grep txt > out.txt
```

Se convierte en:

```
cmd1 → cmd2
```

### Funcionamiento paso a paso

**1.** Inicializar el primer comando

Crear un t_cmd vacío:

```c
argv = NULL
redirs = NULL
next = NULL
```

**2.** Recorrer la lista de tokens

Usar un puntero curr para avanzar token a token.

**3.** `WORD → añadir a argv`

Si el token es WORD, se añade al array de argumentos del comando actual.

**Ejemplo:**

```bash
ls -l /home
→ argv = ["ls", "-l", "/home", NULL]
```

**4.** Redirecciones → asociarlas al comando actual

Tipos:

- '<'  → input
- '>' → output truncate
- '>>' → output append
- '<<' → heredoc

Regla:

Una redirección siempre debe ir seguida de un WORD.

**Ejemplo:**

Código
ls > out.txt
→ redirección OUT con filename "out.txt"

**5.** PIPE → cerrar comando y abrir uno nuevo

Cuando aparece |:

- Se cierra el comando actual
- Se añade a la lista
- Se crea un nuevo t_cmd vacío
- Se continúa con los tokens restantes

Validaciones:
- '|' al inicio → error
- '|' al final → error
- '||' → error

**6.** Validar sintaxis

Errores típicos:

- '|' sin comando antes o después
- '<', '>', '>>', '<<' sin WORD después
- Dos operadores seguidos sin WORD entre ellos
- << |
- '>' al final

Si hay error → liberar todo y devolver NULL.

**7.** Finalizar y devolver la lista

Cuando no quedan tokens:

- Añadir el último comando a la lista
- Devolver la lista completa de t_cmd

### Ejemplo completo

Entrada:

```bash
cat < in.txt | grep hola >> out.txt
```

Tokens:

```bash
WORD("cat")
REDIR_IN("<")
WORD("in.txt")
PIPE("|")
WORD("grep")
WORD("hola")
REDIR_APPEND(">>")
WORD("out.txt")
```

Salida:

Comando 1

```
argv = ["cat"]
redirs = [ IN("in.txt") ]
next → cmd2
```

Comando 2

```
argv = ["grep", "hola"]
redirs = [ APPEND("out.txt") ]
next = NULL
```

**6.** Qué NO debe hacer parse_tokens

- No debe expandir variables
- No debe eliminar comillas
- No debe dividir palabras
- No debe ejecutar nada
- No debe abrir archivos
- No debe crear pipes del sistema
- No debe modificar el entorno

**7.** Resumen final

<u>parse_tokens:</u>

- Entrada: lista de tokens ya expandidos y sin comillas
- Salida: lista de t_cmd con argv, redirecciones y pipeline
- Responsabilidad: construir la estructura semántica del comando
- Validación: detectar errores de sintaxis
- No toca: expansión, comillas, entorno, ejecución
- Es el núcleo del parser semántico y el paso previo al executor.



## Esqueleto conceptual de parse_tokens

### 1. Crear el primer comando vacío

parse_tokens comienza creando un t_cmd vacío:

```c
argv = NULL
redirs = NULL
next = NULL
```

Este será el comando actual.

### 2. Recorrer la lista de tokens

Se recorre token por token:
- Si es WORD → añadir a argv
- Si es redirección → procesar redirección
- Si es PIPE → cerrar comando y abrir uno nuevo

### 3. Procesar tokens tipo WORD

Cuando el token es WORD:
- Se añade al array argv del comando actual
- No se hace nada más

Ejemplo:

```
ls -l /home
→ argv = ["ls", "-l", "/home"]
```

### 4. Procesar redirecciones

Cuando el token es:
- '<'
- '>'
- '>>'
- '<<'

El parser debe:

- Identificar el tipo
- Mirar el siguiente token
- Validar que sea WORD
- Crear un nodo t_redir
- Añadirlo a la lista cmd->redirs

Ejemplo:

```
ls > out.txt
→ redirección tipo TRUNC con file "out.txt"
```

### 5. Procesar pipes

Cuando aparece |:
- Validar que el comando actual tenga al menos un argv o redirección
- Añadir el comando actual a la lista
- Crear un nuevo t_cmd vacío
- Continuar con los tokens restantes

Ejemplo:

```
ls -l | grep txt
→ dos comandos encadenados
```

### 6. Validación de sintaxis

El parser debe detectar errores como:
- '|' al inicio
- '|' al final
- '||'
- '<' sin WORD después
- '>' sin WORD después
- '<<' |
- '>' al final
- Dos operadores seguidos sin WORD entre ellos

Si ocurre un error:
- Liberar todo
- Devolver NULL

### 7. Finalizar

Cuando se acaban los tokens:
- Añadir el último comando a la lista
- Devolver la lista completa de t_cmd

### Resumen final

Estructuras necesarias:
- t_cmd → comando con argv, redirecciones y next
- t_redir → redirección con tipo, file y next
- t_token → tokens ya expandidos y sin comillas

Qué hace parse_tokens:
- Crea un comando vacío
- Recorre tokens
- WORD → añadir a argv
- Redirección → crear nodo y añadir
- PIPE → cerrar comando y abrir otro
- Validar sintaxis
- Devolver lista de comandos

Qué NO hace:
- No expande variables
- No elimina comillas
- No ejecuta nada
- No abre archivos
- No crea pipes del sistema
