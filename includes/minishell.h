#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h> // opendir, readdir, closedir
# include <fcntl.h>  // open
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>    // signal, sigaction, sigemptyset, sigaddset, kill
# include <stdbool.h>	
# include <stdio.h>     // printf, perror
# include <stdlib.h>    // malloc, free, getenv, exit
# include <string.h>    // strerror
# include <sys/ioctl.h> // ioctl
# include <sys/stat.h>  // stat, lstat, fstat
# include <sys/wait.h>  // wait, waitpid, wait3, wait4
# include <term.h>      // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <termios.h>   // tcsetattr, tcgetattr
# include <errno.h>
# include <unistd.h>    // write, read, access, close, fork, execve, dup, dup2,
						// pipe, isatty, ttyname, ttyslot, getcwd, chdir, unlink

# include "structs.h"
# include "environment.h"
# include "tokenizer.h"
# include "expander.h"
# include "cmd.h"
# include "status.h"
# include "shell.h"
# include "parser.h"
# include "utils.h"

# include "builtins.h"
# include "executor.h"

# define BLUE "\033[34m" // azul
# define GRAY "\033[37m" // gris
# define RESET "\033[0m"
# define SOFT_YELLOW "\033[38;5;229m" // amarillo pastel
# define WARM_GRAY "\033[38;5;245m"   // gris cálido

#endif
