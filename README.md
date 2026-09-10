_This project has been created as part of the 42 curriculum by **bconejo-** and **jcolina-**._

# Minishell

## Description

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

1. PS_START: Waits for a command start or a redirection.
2. PS_WORD: Appends arguments to the current command.
3. PS_REDIR: Waits for a target file after finding < or >.
4. PS_AFTER_REDIR: Continues reading arguments or waits for a pipe.
5. PS_PIPE: Initializes a new t_cmd node and resets the cycle.

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

**Prerequisites:** Requires a gcc/clang compiler, make, and the GNU readline library.

```text
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
```

**Execution**

```text
# Interactive Mode
./minishell
minishell % ls -la | grep src > output.txt

# Non-Interactive Mode (via pipes)
echo "echo Hello Minishell" | ./minishell
```

## Resources

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