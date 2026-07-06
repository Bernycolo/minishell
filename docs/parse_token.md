## Objetivo de manage_start

Interpretar el primer token del comando y decidir:

- qué acción corresponde,
- si la secuencia es válida,
- a qué estado debe transicionar.

manage_start solo se ejecuta cuando el parser está en PS_START, es decir, cuando:

- empieza el primer comando de la línea, o
- empieza un comando después de un PIPE.

**¿Qué puede aparecer en PS_START?**

1. **WORD → primer argumento del comando**

<u>Interpretación:</u>

> “Este comando empieza con un nombre o argumento.”

<u>Acciones:</u>

- añadir este WORD a argv
- marcar que el comando ya tiene argumentos
- cambiar estado a PS_WORD

2. **REDIR → el comando empieza con una redirección**

<u>Interpretación:</u>

> “Este comando empieza con una redirección, así que ahora necesito un filename.”

<u>Acciones:</u>

- registrar el tipo de redirección (<, >, >>, <<)
- preparar estructura para filename
- cambiar estado a PS_REDIR

<u>Esto permite comandos válidos como:</u>

```bash
< infile grep foo
```

3. **PIPE → error sintáctico**

<u>Interpretación:</u>

> “Un comando no puede empezar con un pipe.”

<u>Acciones:</u>

- devolver error sintáctico
- abortar el parseo

Aunque tu lexer ya filtra esto, el parser debe tener esta lógica para ser defendible.

4. **END → error sintáctico**

<u>Interpretación:</u>

> “No hay comando. La línea está vacía.”

<u>Acciones:</u>

- devolver error
- abortar

#### Resumen de manage_start
- **Token:** Interpretación	Acción	Nuevo estado
- **WORD:** primer argumento	añadir a argv	PS_WORD
- **REDIR:** comando empieza con redirección	registrar redir	PS_REDIR
- **PIPE:** error	abortar	—
- **END:** error	abortar	—

<u>¿Qué NO hace manage_start?</u>

- No añade más argumentos (eso es PS_WORD).
- No maneja filename (eso es PS_REDIR).
- No maneja pipes (eso es PS_PIPE).
- No maneja errores de secuencias posteriores.
- No interpreta el resto del comando.

Solo decide cómo empieza.

manage_start es como un guardia en la puerta del comando:

- Si ve un WORD, dice: “adelante, este comando empieza con un argumento”.
- Si ve un REDIR, dice: “vale, este comando empieza con una redirección, dame el filename”.
- Si ve un PIPE, dice: “esto es ilegal, no puedes empezar así”.
- Si ve END, dice: “no hay comando, error”.

---

## Objetivo de manage_word

Interpretar el token actual como parte de un comando que ya tiene argumentos, y decidir:

- si es otro argumento,
- si inicia una redirección,
- si cierra el comando por un pipe,
- si termina el comando, 
- o si es un error sintáctico.

**Comportamiento de manage_word**

1. **WORD → añadir argumento**

<u>Interpretación:</u>

> “Otro argumento del comando.”

<u>Acciones:</u>

- añadir el argumento a argv
- incrementar argc
- mantener el estado en PS_WORD

2. **REDIR → iniciar redirección**

<u>Interpretación:</u>

> “Empieza una redirección dentro del comando.”

<u>Acciones:</u>

- registrar el tipo de redirección (pero no leer filename aquí)
- cambiar estado a PS_REDIR

3. **PIPE → cerrar comando y empezar otro**

<u>Interpretación:</u>

> “Este comando termina aquí. Empieza otro.”

<u>Acciones:</u>

- finalizar el comando actual
- crear un nuevo t_cmd
- enlazarlo en la pipeline
- cambiar estado a PS_PIPE

4. **END → fin del comando**

<u>Interpretación:</u>

> “No hay más tokens. Comando completo.”

<u>Acciones:</u>

- terminar el comando
- devolver SUCCESS

5. **Cualquier otra cosa → error**

Aunque tu lexer ya filtra casos raros, conceptualmente:

- un token inesperado aquí es FAILURE

**Tabla de transición en manage_word**

| Token | Interpretación | Acción | Nuevo estado |
|:-----:|:--------------:|:------:|:------------:|
| WORD | otro argumento | añadir a argv | PS_WORD |
| REDIR | empieza redirección | registrar operador | PS_REDIR |
| PIPE | termina comando | crear nuevo comando | PS_PIPE |
| END |fin | terminar | — |
| otro | error | abortar | — |


Piensa en manage_word como el parser diciendo:

> Estoy leyendo argumentos.
> - Si me das otro WORD, lo añado.
> - Si me das una redirección, la empiezo.
> - Si me das un pipe, cierro este comando y abro otro.
> - Si me das END, termino.
> - Si me das otra cosa, error.”

**Resumen**

manage_word:

- añade argumentos
- inicia redirecciones
- maneja pipes
- detecta fin de comando
- mantiene la gramática correcta
- no consume filename (eso es PS_REDIR)
- no crea comandos nuevos salvo en PIPE

---

### Objetivo de manage_redir

- Validar que el token actual es un WORD (el filename).
- Crear la redirección en la estructura del comando.
- Cambiar el estado a PS_AFTER_REDIR.
- Detectar errores si el token no es un WORD.

**Comportamiento de manage_redir**

1. **WORD → filename válido**

<u>Interpretación:</u>

> “Este WORD es el filename de la redirección.”

<u>Acciones:</u>

- crear una nueva redirección con:
    - tipo = operador leído previamente
    - filename = este WORD
- añadirla a cmd->redirs
- cambiar estado a PS_AFTER_REDIR

2. **REDIR → error**

<u>Interpretación:</u>

> “Dos operadores seguidos sin filename.”

Ejemplo inválido:

```bash
cat > > file
```

<u>Acción:</u>

- devolver FAILURE

3. **PIPE → error**

<u>Interpretación:</u>

> “Pipe sin filename.”

Ejemplo inválido:

```bash
ls < | wc
```

<u>Acción:</u>

- devolver FAILURE

4. **END → error**

<u>Interpretación:</u>

> “Redirección sin filename.”

Ejemplo inválido:

```bash
ls <
```

<u>Acción:</u>

- devolver FAILURE

Tabla de transición en manage_redir

| Token | Interpretación | Acción | Nuevo estado |
|:-----:|:-----:|:-----:|:-----:|
| WORD | filename | crear redirección | PS_AFTER_REDIR |
| REDIR | operador sin filename | error | — |
| PIPE | pipe sin filename | error | — |
| END | redirección incompleta | error | — |

Piensa en manage_redir como el parser diciendo:

> “Me acabas de dar un operador de redirección.
> Ahora SOLO acepto un WORD como filename.
> Si me das cualquier otra cosa, es un error.”

**Resumen**

manage_redir:

- valida que el filename sea un WORD
- crea la redirección en el comando
- transiciona a PS_AFTER_REDIR
- detecta todos los errores sintácticos relacionados con redirecciones
- mantiene la gramática correcta del minishell
- no consume operadores ni pipes
- no añade argumentos

---

### Objetivo de manage_after_redir

- Validar qué token viene después del filename.
- Asegurar que no se añadan argumentos inmediatamente después del filename.
- Permitir nuevas redirecciones.
- Permitir pipes.
- Permitir fin de comando.
- Detectar errores sintácticos.

Cuando el parser está en PS_AFTER_REDIR, significa:

> “Acabo de leer el filename de una redirección.
> Ahora necesito saber qué viene después, y no puede ser un WORD.”

Este estado existe para evitar ambigüedades y errores como:

```bash
grep < file1 file2     # ERROR
ls < infile > outfile  # OK
ls < infile | wc       # OK
```

**Comportamiento de manage_after_redir**

1. **REDIR → nueva redirección**

<u>Interpretación:</u>

> “Después del filename viene otra redirección.”

<u>Acciones:</u>

- registrar el operador de redirección
- cambiar estado a PS_REDIR

Ejemplo válido:

```bash
ls < infile > outfile
```

2. **PIPE → cerrar comando y empezar otro**

<u>Interpretación:</u>

> “El comando termina aquí. Empieza otro.”

<u>Acciones:</u>

- cerrar el comando actual
- crear un nuevo t_cmd
- enlazarlo en la pipeline
- cambiar estado a PS_PIPE

Ejemplo válido:

```bash
ls < infile | wc
```

3. **END → fin del comando**

<u>Interpretación:</u>

> “No hay más tokens. Comando completo.”

<u>Acciones:</u>

- terminar el comando
- devolver SUCCESS

Ejemplo válido:

```bash
ls < infile
```

4. **WORD → error sintáctico**

<u>Interpretación:</u>

> “Un argumento inmediatamente después del filename es ilegal.”

Ejemplo inválido:

```bash
grep < file1 file2
```

<u>Acciones:</u>

- devolver FAILURE

Este es el error más importante que detecta este estado.

**Tabla de transición en manage_after_redir**

Token	Interpretación	Acción	Nuevo estado
REDIR	nueva redirección	registrar operador	PS_REDIR
PIPE	termina comando	crear nuevo comando	PS_PIPE
END	fin	terminar	—
WORD	argumento ilegal	error	—

Piensa en manage_after_redir como el parser diciendo:

> “Ya tengo el filename.
> Ahora solo acepto:
> - otra redirección,
> - un pipe,
> - o el fin del comando.
> - Si me das un WORD, es un error.”

**Resumen**

manage_after_redir:

- valida que no haya argumentos después del filename
- permite nuevas redirecciones
- permite pipes
- permite fin de comando
- detecta errores sintácticos reales
- mantiene la gramática correcta del minishell
- no añade argumentos
- no crea redirecciones (eso es PS_REDIR)

---

### Objetivo de manage_pipe

- Validar que el token actual es un inicio válido de comando.
- Crear un nuevo t_cmd y enlazarlo a la pipeline.
- Cambiar el estado a PS_START (o directamente PS_WORD / PS_REDIR según el token).
- Detectar errores si el token no es válido.

Cuando el parser está en PS_PIPE, significa:

> “Acabo de leer un |.
> El comando anterior está cerrado.
> Ahora NECESITO iniciar un nuevo comando.”

Este estado es estricto: después de un pipe solo puede venir:

- un WORD (primer argumento del nuevo comando), o
- una REDIR (nuevo comando empieza con redirección).

Cualquier otra cosa es error sintáctico.

**Comportamiento de manage_pipe**

1. **WORD → primer argumento del nuevo comando**

<u>Interpretación:</u>

> “El nuevo comando empieza con un argumento.”

<u>Acciones:</u>

- crear un nuevo t_cmd
- enlazarlo al comando anterior
- añadir el argumento
- cambiar estado a PS_WORD

Ejemplo válido:

```bash
ls -l | wc -l
```

2. **REDIR → nuevo comando empieza con redirección**

<u>Interpretación:</u>

> “El nuevo comando empieza con una redirección.”

<u>Acciones:</u>

- crear un nuevo t_cmd
- enlazarlo al comando anterior
- registrar el operador de redirección
- cambiar estado a PS_REDIR

Ejemplo válido:

```bash
ls | < infile wc
```

3. **PIPE → error sintáctico**

<u>Interpretación:</u>

> “Dos pipes seguidos no son válidos.”

Ejemplo inválido:

```bash
ls || wc
```

<u>Acciones:</u>

- devolver FAILURE

4. **END → error sintáctico**

<u>Interpretación:</u>

> “Un pipe no puede estar al final del comando.”

Ejemplo inválido:

```bash
ls |
```

<u>Acciones:</u>

- devolver FAILURE

**Tabla de transición en manage_pipe**

| Token | Interpretación | Acción | Nuevo estado |
|:-----:|:-----:|:-----:|:-----:|
| WORD | nuevo comando | crear comando + añadir arg | PS_WORD |
| REDIR | nuevo comando con redirección | registrar operador | PS_REDIR |
| PIPE | pipe doble | error | — |
| END | pipe al final | error | — |

Piensa en manage_pipe como el parser diciendo:

> “Acabo de cerrar un comando.
>  Ahora SOLO acepto:
> - un WORD para empezar el nuevo comando,
> - una REDIR para empezar el nuevo comando con redirección.
>
> Si me das un PIPE o END, es un error.”

**Resumen**

manage_pipe:

- crea un nuevo comando en la pipeline
- valida que el nuevo comando empieza correctamente
- permite WORD y REDIR
- detecta pipes dobles
- detecta pipes al final
- mantiene la gramática correcta del minishell
- no añade argumentos del comando anterior
- no consume filename (eso es PS_REDIR)

---


