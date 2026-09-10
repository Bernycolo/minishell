# Minishell

> 🇪🇸 [Versión en Español](#-versión-en-español) | 🇬🇧 [English Version](#-english-version)

---

## 🇪🇸 Versión en Español

_Este proyecto ha sido creado como parte del currículo de 42 por **bconejo-** y **jcolina-**._

**Índice**
1. [Descripción](#descripción)
2. [Arquitectura y Flujo de Datos](#arquitectura-y-flujo-de-datos)
3. [Instrucciones](#instrucciones)
4. [Recursos](#recursos)

## Descripción
[⬆️ Volver al Índice](#-versión-en-español)

El objetivo de este proyecto es crear una shell simple en C que imite el comportamiento central de una shell Bash de Unix. La shell lee la entrada del usuario, la tokeniza, expande variables y comillas, la analiza sintácticamente mediante una Máquina de Estados Finitos (FSM) y finalmente ejecuta los comandos resultantes, gestionando rigurosamente los procesos, los descriptores de archivos, las señales y el estado del entorno.

<u>La shell soporta:</u>

- Prompt interactivo y modo no interactivo por tuberías (vía isatty).
- Comandos integrados (Built-ins): cd, echo, env, exit, export, pwd, unset.
- Expansión de variables de entorno ($VAR, $?).
- Manejo de comillas simples (literales) y dobles (expansibles).
- Tuberías / Pipes (|).
- Redirecciones (<, >, >>, << heredoc).
- Manejo de señales (Ctrl+C, Ctrl+D, Ctrl+\) mediante gestión de estados.

El proyecto es altamente modular: carpetas y archivos separados manejan el análisis léxico (lexer, tokenizer), la expansión (expander), el análisis sintáctico (parser), la ejecución (executor) y los comandos integrados (builtins).

## Arquitectura y Flujo de Datos
[⬆️ Volver al Índice](#-versión-en-español)

La shell procesa cada línea de entrada a través de un flujo secuencial de componentes. A diferencia de las implementaciones basadas en árboles binarios (AST), nuestro Minishell utiliza una estructura de lista enlazada de comandos perfectamente adaptada para tuberías secuenciales.

### Resumen del Flujo

```text
┌──────────────┐
│Entrada de Usr│  (readline / get_next_line)
└──────┬───────┘
       │  cadena cruda
       ▼
┌──────────────┐
│  Tokenizer   │  (tokenizer.c) Divide la entrada cruda en tokens.
└──────┬───────┘
       │  lista enlazada: t_token
       ▼
┌──────────────┐
│              │
│   Expansor   │  (expander.c) Resuelve $VAR y $? dentro de tokens.
│              │  Elimina comillas aplicando la semántica correcta.
└──────┬───────┘
       │  lista t_token (valores resueltos)
       ▼
┌──────────────┐
│   & Lexer    │  (lexer.c) Valida la sintaxis (evita pipes vacíos, etc).
└──────┬───────┘
       │  lista t_token
       ▼
┌──────────────┐
│              │
│  Analizador  │  (parse_token.c) Usa una Máquina de Estados (FSM)
│  Sintáctico  │  para construir una lista de comandos lista para ejecutar.
└──────┬───────┘
       │  lista enlazada: t_cmd
       ▼
┌──────────────┐
│              │
│   Ejecutor   │  (exec.c) Clasifica built-ins vs binarios.
│              │  Crea procesos hijos (fork), maneja pipes y redirecciones.
└──────┬───────┘
       │  estado de salida → $? (shell->last_status)
       ▼
┌──────────────┐
│    Salida    │  stdout / stderr / archivos
└──────────────┘
```

### Estructuras de Datos Clave

Nuestra arquitectura se basa en dos estructuras principales interconectadas:

```text
t_cmd (Comandos conectados por Pipes)
┌───────────────────┐
│ arg        char** │ -> ["ls", "-la", NULL]
│ argc       int    │ -> 2
│ is_builtin int    │ -> 0
│ redirs     t_redir│ -> Lista de redirecciones para ESTE comando
│ next       t_cmd* │ -> Siguiente comando en la tubería
└───────────────────┘

t_redir (Lista de Redirecciones)
┌───────────────────┐
│ type       enum   │ -> TRUNC, APPEND, INPUT, HEREDOC
│ target     char*  │ -> "file.txt" o "EOF"
│ redir_in   int    │ -> FD de entrada (por defecto STDIN)
│ redir_out  int    │ -> FD de salida (por defecto STDOUT)
│ next       t_redir│ -> Siguiente redirección
└───────────────────┘
```

### El Parser (FSM)

El analizador sintáctico utiliza una Máquina de Estados Finitos para procesar los tokens de forma lineal y segura. Los estados definidos son:

1. **PS_START**: Espera el inicio de un comando o una redirección.
2. **PS_WORD**: Agrupa argumentos para el comando actual.
3. **PS_REDIR**: Espera un archivo destino tras encontrar < o >.
4. **PS_AFTER_REDIR**: Continúa leyendo argumentos o espera un pipe.
5. **PS_PIPE**: Inicializa un nuevo nodo t_cmd y reinicia el ciclo.

### Señales y Máquina de Estados Global

Para cumplir con la estricta norma que permite una única variable global, implementamos g_signal como un rastreador de contexto. Esto nos permite modificar el comportamiento de las señales y eventos del sistema dependiendo de lo que esté haciendo la shell en ese momento exacto:

| Señal / Evento | Contexto (`g_signal`) | Comportamiento | Código `$?` |
|:---:|:---:|:---:|:---:|
| `Ctrl+C` (SIGINT) | `S_BASE` (Interactivo) | Limpia la entrada actual, cancela la línea y muestra un nuevo prompt. | 130 |
| `Ctrl+C` (SIGINT) | `S_CMD` (Proceso hijo) | Interrumpe el proceso hijo. El padre imprime un salto de línea. | 130 |
| `Ctrl+C` (SIGINT) | `S_HEREDOC` (Heredoc) | Cierra `STDIN` forzosamente, cancelando el heredoc y volviendo al prompt. | 130 |
| `Ctrl+\` (SIGQUIT) | `S_BASE` / `S_HEREDOC` | Ignorado (`SIG_IGN`) por la shell. No hace absolutamente nada. | — |
| `Ctrl+\` (SIGQUIT) | `S_CMD` (Proceso hijo) | Termina el hijo. El padre imprime `Quit (core dumped)`. | 131 |
| `Ctrl+D` (EOF) | Interactivo (vacío) | Libera memoria, limpia el historial y sale de la shell limpiamente.. | 0 |
| `Ctrl+D` (EOF) | `S_HEREDOC` (Heredoc) | Cierra el heredoc normalmente, guardando lo escrito hasta el momento. | 0 |

La señal Ctrl+\ (`SIGQUIT`) es ignorada (`SIG_IGN`) en el proceso padre, pero restaura su comportamiento por defecto (`SIG_DFL`) en los procesos hijos para permitir el "`Quit (core dumped)`".

### Ejecución y Descriptores de Archivos

El ejecutor se bifurca dependiendo de si maneja un comando único o una tubería:

- **Comando Único (execute_single):** Si es un built-in, se ejecuta en el proceso padre usando dup() para guardar STDIN/STDOUT y restaurarlos después. Si es un binario, realiza un fork().

- **Tubería (execute_pipeline):** Enlaza múltiples procesos iterando sobre la lista t_cmd. Maneja pipe() de forma iterativa, gestionando prev_fd para encadenar la salida de un hijo con la entrada del siguiente, cerrando meticulosamente los descriptores no utilizados en el padre para evitar fugas de descriptores de archivos (FD Leaks).

### Árbol de Flujo de Ejecución

El punto de entrada principal para la ejecución es executor(). El flujo se ramifica lógicamente basándose en si existe una tubería o si es un comando único, optimizando la creación de procesos y la gestión de los descriptores de archivos (FD).

```text
executor(shell)
       │
       ├─ classify_cmd()           (Marca comandos como built-ins o externos)
       ├─ prepare_redirections()   (Evalúa/abre todos los archivos y heredocs)
       │
       ├─ ¿cmd->next == NULL? (Comando Único)
       │         │
       │         └─ execute_single()
       │                 │
       │                 ├─ ¿Builtin? ──SÍ──▶ apply_redirs() + exec_builtin()
       │                 │                      [Ejecuta en PADRE, guardando/restaurando FDs originales]
       │                 │
       │                 └─ ¿Externo? ──SÍ──▶ exec_cmd()
       │                                        ├─ fork()
       │                                        ├─ Hijo: apply_redirs() + execve_cmd()
       │                                        └─ Padre: waitpid() + close_cmd_redirs()
       │
       └─ ¿cmd->next != NULL? (Tubería)
                 │
                 └─ execute_pipeline()
                         │
                         ├─ Bucle iterativo por cada comando:
                         │      ├─ pipe(pipefd)
                         │      ├─ fork()
                         │      ├─ Hijo: child_exec()
                         │      │          └─ dup2(prev_fd/pipefd) + apply_redirs() + execve/builtin
                         │      └─ Padre: close_pipe()
                         │                 └─ Cierra el extremo de escritura y actualiza prev_fd
                         │
                         └─ Tras el bucle: exec_pipeline_cont()
                                └─ waitpid() para el último PID + espera a los hijos restantes + close_pids()
```

## Instrucciones
[⬆️ Volver al Índice](#-versión-en-español)

> ⚠️ **Nota Importante para MacOs:** Este proyecto utiliza la biblioteca GNU Readline instalada a través de Homebrew. El `Makefile` detectará automáticamente tu arquitectura (Intel o Apple Silicon) para compilar sin problemas.

**Requisitos previos:** Requiere un compilador gcc/clang, make y la biblioteca GNU readline.

```bash
# Instalación de readline en MacOs
brew install readline

# Compilar el proyecto
make

# Limpiar archivos objeto
make clean

# Limpieza total de archivos
make fclean

# Recompilación completa
make re

# Ejecutar con Valgrind
make valgrind

# Compilar con Sanitizer
make asan
```

### Ejecución:

```bash
# Modo Interactivo
./minishell
minishell % ls -la | grep src > salida.txt

# Modo No Interactivo (mediante tuberías)
echo "echo Hola Minishell" | ./minishell
```

## Recursos
[⬆️ Volver al Índice](#-versión-en-español)

### Documentación y manuales de referencia

*   [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html): Esencial para entender los comportamientos centrales de la shell, reglas de expansión y códigos de salida integrados.

*   [GNU Readline Library Documentation](https://tiswww.case.edu/php/chet/readline/rluserman.html): Utilizado para implementar el prompt interactivo y la gestión del historial.

*   **Páginas Man de Unix:** Manuales muy consultados para llamadas al sistema, incluyendo fork(2), execve(2), waitpid(2), pipe(2), dup2(2) y signal(7).

### Uso de IA

Durante el desarrollo de este proyecto, se utilizó Inteligencia Artificial como herramienta de apoyo para tareas específicas, adhiriéndose estrictamente a las pautas de integridad académica. El uso se limitó a las siguientes áreas:

| Tarea / Objectivo | Área del projecto / Implementación |
| :--- | :--- |
| **Depuración de Fugas de Memoria y FD** | Proporcionó análisis sobre los reportes de Valgrind, ayudando a identificar y parchear fugas de descriptores de archivos durante la ejecución de tuberías (específicamente en `close_pids` y `redir.c`). |
| **Documentación y Comentarios** | Generó comentarios de bloque estandarizados estilo Doxygen para el código fuente y ayudó a estructurar los diagramas arquitectónicos para este `README.md`. |


---


## 🇬🇧 English version
[⬆️ Back to Top](#minishell)

_This project has been created as part of the 42 curriculum by **bconejo-** and **jcolina-**._

**Table of Contents**
1. [Description](#description)
2. [Architecture and Data Flow](#architecture-and-data-flow)
3. [Instructions](#instructions)
4. [Resources](#resources)

## Description
[⬆️ Back to Top](#-english-version)

The goal of this project is to create a simple shell in C that mimics the core behavior of a Unix Bash shell. The shell reads user input, tokenizes it, expands variables and quotes, parses it using a Finite State Machine (FSM), and finally executes the resulting commands, rigorously managing processes, file descriptors, signals, and environment state.

<u>The shell supports:</u>

- Interactive prompt and non-interactive piped mode (via isatty).
- Built-in commands: cd, echo, env, exit, export, pwd, unset.
- Environment variable expansion ($VAR, $?).
- Single (literal) and double (expandable) quote handling.
- Pipes (|).
- Redirections (<, >, >>, << heredoc).
- Signal handling (Ctrl+C, Ctrl+D, Ctrl+\) via state management.

The project is highly modular: separate folders and files handle lexing (lexer, tokenizer), expansion (expander), parsing (parser), execution (executor), and built-ins (builtins).

## Architecture and Data Flow
[⬆️ Back to Top](#-english-version)

The shell processes each line of input through a sequential pipeline of components. Unlike AST binary tree implementations, our Minishell uses a linked list of commands structure perfectly suited for sequential pipelines.

### Flow Overview

```text
┌──────────────┐
│  User Input  │  (readline / get_next_line)
└──────┬───────┘
       │  raw string
       ▼
┌──────────────┐
│  Tokenizer   │  (tokenizer.c) Splits raw input into tokens.
└──────┬───────┘
       │  linked list: t_token
       ▼
┌──────────────┐
│              │
│   Expander   │  (expander.c) Resolves $VAR and $? inside tokens.
│              │  Removes quotes applying correct semantics.
└──────┬───────┘
       │  t_token list (resolved values)
       ▼
┌──────────────┐
│   & Lexer    │  (lexer.c) Validates syntax (prevents empty pipes, etc).
└──────┬───────┘
       │  t_token list
       ▼
┌──────────────┐
│              │
│    Parser    │  (parse_token.c) Uses a Finite State Machine (FSM)
│              │  to build a list of commands ready for execution.
└──────┬───────┘
       │  linked list: t_cmd
       ▼
┌──────────────┐
│              │
│   Executor   │  (exec.c) Classifies built-ins vs binaries.
│              │  Forks child processes, handles pipes and redirections.
└──────┬───────┘
       │  exit status → $? (shell->last_status)
       ▼
┌──────────────┐
│    Output    │  stdout / stderr / files
└──────────────┘
```

### Key Data Structures

Our architecture relies on two main interconnected structures:

```text
t_cmd (Commands connected by Pipes)
┌───────────────────┐
│ arg        char** │ -> ["ls", "-la", NULL]
│ argc       int    │ -> 2
│ is_builtin int    │ -> 0
│ redirs     t_redir│ -> Redirections list for THIS command
│ next       t_cmd* │ -> Next command in the pipeline
└───────────────────┘

t_redir (Redirections List)
┌───────────────────┐
│ type       enum   │ -> TRUNC, APPEND, INPUT, HEREDOC
│ target     char*  │ -> "file.txt" or "EOF"
│ redir_in   int    │ -> Input FD (default STDIN)
│ redir_out  int    │ -> Output FD (default STDOUT)
│ next       t_redir│
└───────────────────┘
```

### The Parser (FSM)

The parser utilizes a Finite State Machine to process tokens linearly and safely. The defined states are:

1. **PS_START**: Waits for a command start or a redirection.
2. **PS_WORD**: Appends arguments to the current command.
3. **PS_REDIR**: Waits for a target file after finding < or >.
4. **PS_AFTER_REDIR**: Continues reading arguments or waits for a pipe.
5. **PS_PIPE**: Initializes a new t_cmd node and resets the cycle.

### Signals and Global State Machine

To comply with the strict norm that allows only one global variable, we implemented `g_signal` as a **context tracker**. This allows us to modify the behavior of system signals and events depending on what the shell is doing at that exact moment:

| Signal / Event | Context (`g_signal`) | Behavior | `$?` Code |
|:---:|:---:|:---:|:---:|
| `Ctrl+C` (SIGINT) | `S_BASE` (Interactive) | Clears current input, cancels the line, and displays a new prompt. | 130 |
| `Ctrl+C` (SIGINT) | `S_CMD` (Child process) | Interrupts the child process. The parent prints a newline. | 130 |
| `Ctrl+C` (SIGINT) | `S_HEREDOC` (Heredoc) | Force-closes `STDIN`, canceling the heredoc and returning to the prompt. | 130 |
| `Ctrl+\` (SIGQUIT) | `S_BASE` / `S_HEREDOC` | Ignored (`SIG_IGN`) by the shell. Does absolutely nothing. | — |
| `Ctrl+\` (SIGQUIT) | `S_CMD` (Child process) | Terminates the child. The parent prints `Quit (core dumped)`. | 131 |
| `Ctrl+D` (EOF) | Interactive (empty) | Frees memory, clears history, and exits the shell cleanly. | 0 |
| `Ctrl+D` (EOF) | `S_HEREDOC` (Heredoc) | Closes the heredoc normally, saving the input provided so far. | 0 |

Ctrl+\ (SIGQUIT) is ignored (SIG_IGN) in the parent process, but restores default behavior (SIG_DFL) in child processes to allow "Quit (core dumped)".

### Execution and File Descriptors

The executor branches based on whether it handles a single command or a pipeline:

- **Single Command (execute_single):** If it's a built-in, it runs in the parent process using dup() to save STDIN/STDOUT and restore them afterward. If it's a binary, it performs a fork().

- **Pipeline (execute_pipeline):** Links multiple processes by iterating over the t_cmd list. It handles pipe() iteratively, managing prev_fd to chain the output of one child to the input of the next, meticulously closing unused descriptors in the parent to prevent File Descriptor Leaks.

### Execution Flow Tree

The main entry point for execution is `executor()`. The flow branches logically based on whether a pipeline is present or if it's a single command, optimizing the creation of processes and file descriptor (FD) management.

```text
executor(shell)
       │
       ├─ classify_cmd()           (Flags commands as built-ins or externals)
       ├─ prepare_redirections()   (Evaluates/opens all files and heredocs)
       │
       ├─ is cmd->next == NULL? (Single Command)
       │         │
       │         └─ execute_single()
       │                 │
       │                 ├─ Builtin? ──YES──▶ apply_redirs() + exec_builtin()
       │                 │                      [Runs in PARENT, saving/restoring original FDs]
       │                 │
       │                 └─ External? ─YES──▶ exec_cmd()
       │                                        ├─ fork()
       │                                        ├─ Child: apply_redirs() + execve_cmd()
       │                                        └─ Parent: waitpid() + close_cmd_redirs()
       │
       └─ is cmd->next != NULL? (Pipeline)
                 │
                 └─ execute_pipeline()
                         │
                         ├─ Iterative loop over each command:
                         │      ├─ pipe(pipefd)
                         │      ├─ fork()
                         │      ├─ Child: child_exec()
                         │      │          └─ dup2(prev_fd/pipefd) + apply_redirs() + execve/builtin
                         │      └─ Parent: close_pipe()
                         │                 └─ Closes write end and updates prev_fd
                         │
                         └─ After loop: exec_pipeline_cont()
                                └─ waitpid() for last PID + waits remaining children + close_pids()
```

## Instructions
[⬆️ Back to Top](#-english-version)

**Prerequisites:** Requires a gcc/clang compiler, make, and the GNU readline library.

```bash
# Installing readline on MacOs
brew install readline

# Build the project
make

# Clean object files
make clean

# Full clean files
make fclean

# Full rebuild
make re

# Test with Valgrind
make valgrind

# Build the project with Sanitizer
make asan
```

**Execution**

```bash
# Interactive Mode
./minishell
minishell % ls -la | grep src > output.txt

# Non-Interactive Mode (via pipes)
echo "echo Hello Minishell" | ./minishell
```

## Resources
[⬆️ Back to Top](#-english-version)

### Documentation & Reference Manuals
*   [GNU Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html): Essential for understanding core shell behaviors, expansion rules, and built-in exit codes.
*   [GNU Readline Library Documentation](https://tiswww.case.edu/php/chet/readline/rluserman.html): Used for implementing the interactive prompt and history management.
*   **Unix Man Pages**: Highly referenced manuals for system calls including `fork(2)`, `execve(2)`, `waitpid(2)`, `pipe(2)`, `dup2(2)`, and `signal(7)`.

### AI Usage
During the development of this project, Artificial Intelligence was utilized as a supportive tool to assist with specific tasks, strictly adhering to academic integrity guidelines. The usage was limited to the following areas:

| Task / Objective | Project Area / Implementation |
| :--- | :--- |
| **Memory & FD Leak Debugging** | Provided analysis on Valgrind reports, helping to identify and patch file descriptor leaks during pipeline execution (specifically in `close_pids` and `redir.c`). |
| **Documentation & Comments** | Generated standardized Doxygen-style block comments for the source code and helped structure the architectural diagrams for this `README.md`. |
