#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>	// write, read, access, close, fork, execve, dup, dup2,
			// pipe, isatty, ttyname, ttyslot, getcwd, chdir, unlink
# include <fcntl.h>	// open
# include <stdio.h>	// printf, perror
# include <stdlib.h>	// malloc, free, getenv, exit
# include <string.h>	// strerror
# include <stdio.h>	// printf, perror
# include <stdlib.h>	// malloc, free, getenv, exit
# include <string.h>	// strerror
# include <sys/wait.h>	// wait, waitpid, wait3, wait4
# include <signal.h>	// signal, sigaction, sigemptyset, sigaddset, kill
# include <sys/stat.h>	// stat, lstat, fstat
# include <dirent.h>	// opendir, readdir, closedir
# include <termios.h>	// tcsetattr, tcgetattr
# include <sys/ioctl.h>	// ioctl
# include <term.h>	// tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs

# include "libft.h"
# include <limits.h>

# define BLUE	"\033[34m"	// azul
# define GRAY	"\033[37m"	// gris
# define RESET	"\033[0m"
# define SOFT_YELLOW "\033[38;5;229m"  // amarillo pastel
# define WARM_GRAY   "\033[38;5;245m"  // gris cálido
#endif
