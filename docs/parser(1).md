# Pasos a realizar en el parseo de una línea de comando 

## PASO 1 — Tokenizer (separar palabras y operadores)

El parser no empieza hasta que el tokenizer termina.

<u>El **tokenizer** debe:</u>

- saltar espacios
- separar palabras
- separar operadores (|, <, >, <<, >>)
- respetar comillas
- NO expandir variables
- NO quitar comillas
- NO validar sintaxis

<u>**Salida:**</u> lista de tokens.

<u>**Entrada:**</u>>

```bash
echo "hola mundo" | wc -l >> out.txt
```

Tokenizer produce:

```text
[WORD:"echo"]
[WORD:""hola mundo""]
[PIPE:"|"]
[WORD:"wc"]
[WORD:"-l"]
[REDIR_APPEND:">>"]
[WORD:"out.txt"]
```

## PASO 2 — Validación léxica (errores básicos)

<u>**Aquí detectas errores que el tokenizer no puede detectar:**</u>

- comillas sin cerrar
- operadores inválidos (>>>, ><, ||, |>, etc.)
- redirecciones sin palabra después
- pipeline empezando o terminando en |

Ejemplos de errores:

```bash
echo "hola
cmd >> > out
| ls
```

Esto **NO** construye t_cmd todavía.


## PASO 3 — Expansión de variables ($VAR)

<u>**Ahora sí:**</u>

- expandes $HOME, $USER, $?, etc.
- respetas comillas simples (no expanden)
- expandes dentro de comillas dobles
- expandes fuera de comillas

**Ejemplo:**

```bash
echo "$USER"

→ "bernardo"
```

**Salida:** tokens con valores expandidos.

## PASO 4 — Eliminación de comillas

Ahora quitas las comillas del valor del token, pero sin romper el contenido.

**Ejemplo:**

Token:
```"hola mundo"``` → ```hola mundo```

Esto es importante porque argv no debe contener comillas.

## PASO 5 — Construcción de comandos (t_cmd)

Ahora sí empieza el parser semántico.

Recorres la lista de tokens y construyes:

- comandos
- argumentos (argv)
- redirecciones
- pipeline (next)

**Ejemplo:**

```bash
echo hola | wc -l > out.txt
```

Produce dos nodos t_cmd:

- Comando 1

```c
argv = ["echo", "hola", NULL]
infile = NULL
outfile = NULL
append = 0
next → comando 2
```

- Comando 2

```c
argv = ["wc", "-l", NULL]
outfile = "out.txt"
append = 0
next = NULL
```

## PASO 6 — Validación semántica

Aquí detectas errores como:

```bash
echo > > out
ls | | wc
cat <
| wc
wc |
```

Si algo falla → error de sintaxis.

## PASO 7 — Resultado final: lista de t_cmd

El parser devuelve:

```
t_cmd *cmd;
```

El executor recibe esta lista y ya no necesita interpretar nada.

## Resumen en 7 pasos

1. Tokenizer → separar palabras y operadores

2. Validación léxica → comillas, operadores inválidos

3. Expansión $VAR

4. Eliminar comillas

5. Construir t_cmd

6. Validación semántica

7. Devolver lista de comandos al executor

# Desglose de pasos

## 1. TOKENIZER

El **Tokenizer** convierte la línea cruda del usuario en una lista de tokens (t_token) donde cada token representa:

- una palabra
- un operador (|, <, >, <<, >>)
- respetando comillas
- sin expandir variables
- sin validar sintaxis
- sin construir t_cmd

El tokenizer es puramente léxico.

### PASO 1 — Saltar espacios

El tokenizer debe ignorar espacios entre tokens.

<u>Regla:</u>

	Un token nunca empieza por un espacio.

### PASO 2 — Detectar operadores (1 y 2 caracteres)

<u>Regla de oro:</u>

- Primero detecta operadores de 2 caracteres (<<, >>).
- Si no coinciden, detecta operadores de 1 carácter (<, >, |).

**Ejemplos:**

Entrada:

```a>>b```

Tokens:

```c
[WORD:"a"]
[REDIR_APPEND:">>"]
[WORD:"b"]
```

### PASO 3 — Detectar palabras

Una palabra es:

Una secuencia de caracteres que **NO** son operadores ni espacios, respetando comillas.

**Ejemplo:**

```hola>>mundo```

Tokens:

```c
[WORD:"hola"]
[REDIR_APPEND:">>"]
[WORD:"mundo"]
```

### PASO 4 — Manejo de comillas

El tokenizer **NO** elimina comillas, solo las respeta para no cortar palabras.

<u>Reglas:</u>

- ```"hola mundo"``` → un solo token
- ```'a b c'``` → un solo token
- ```"hola>mundo"``` → un solo token (no detecta > dentro)

**Ejemplo:**

Entrada:

```echo "hola>mundo"```

Tokens:

```c
[WORD:"echo"]
[WORD:""hola>mundo""]
```

### PASO 5 — Crear tokens

Cada token es un nodo:

```c
typedef struct s_token
{
    char            *value;
    t_toktype       type;
    struct s_token  *next;
}   t_token;
```

El tokenizer solo rellena esto, nada más.

### PASO 6 — Clasificar tokens

El tokenizer asigna:
- TOK_WORD
- TOK_PIPE
- TOK_REDIR_IN
- TOK_REDIR_OUT
- TOK_REDIR_APPEND
- TOK_HEREDOC

**Ejemplo:**

```>>``` → ```TOK_REDIR_APPEND```

### PASO 7 — Devolver la lista enlazada

El resultado final del tokenizer es:

```t_token *tokens;```

El parser semántico recibirá esta lista.

### EJEMPLO COMPLETO DEL TOKENIZER

Entrada:

```bash
echo "hola mundo" | wc -l >> out.tx
```

Salida del tokenizer:

```c
[WORD:"echo"]
[WORD:""hola mundo""]
[PIPE:"|"]
[WORD:"wc"]
[WORD:"-l"]
[REDIR_APPEND:">>"]
[WORD:"out.txt"]
```

Nada de expansión, nada de quitar comillas, nada de sintaxis.

### RESUMEN DEL PASO 1 (TOKENIZER)

- Saltar espacios
- Detectar operadores (<<, >>, <, >, |)
- Detectar palabras
- Respetar comillas
- Crear tokens
- Clasificar tokens
- Devolver lista enlazada

El tokenizer no interpreta, no valida, no expande, no construye comandos.

