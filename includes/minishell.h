/**
 * @file minishell.h
 * @author bconejo-
 * @brief 
 * @version 0.1
 * @date 2026-06-20
 * 
 * @copyright Copyright (c) 2026
 * 
 */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h> // opendir, readdir, closedir
# include <fcntl.h>  // open
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>    // signal, sigaction, sigemptyset, sigaddset, kill
# include <stdio.h>     // printf, perror
# include <stdlib.h>    // malloc, free, getenv, exit
# include <string.h>    // strerror
# include <sys/ioctl.h> // ioctl
# include <sys/stat.h>  // stat, lstat, fstat
# include <sys/wait.h>  // wait, waitpid, wait3, wait4
# include <term.h>      // tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs
# include <termios.h>   // tcsetattr, tcgetattr
# include <unistd.h>    // write, read, access, close, fork, execve, dup, dup2,
						// pipe, isatty, ttyname, ttyslot, getcwd, chdir, unlink
# include "tokenizer.h"
# include "environment.h"

# define BLUE "\033[34m" // azul
# define GRAY "\033[37m" // gris
# define RESET "\033[0m"
# define SOFT_YELLOW "\033[38;5;229m" // amarillo pastel
# define WARM_GRAY "\033[38;5;245m"   // gris cálido

/**
 * @brief Represents a node in the command linked list
 * 
*/
typedef struct s_cmd
{
	char	**arg;		// argumentos del comando
	char	*infile;	// redirección de entrada
	char	*outfile;	// redirección de salida
	int		append;		// si es >> o >
	int		is_builtin;	// si es builtin
	struct s_cmd	*next;
}					t_cmd;



/**
 * @struct s_redir
 * @brief Represents a single redirection associated with a command.
 *
 */
/*
typedef struct s_redir
{
    int             type;        Redirection type
    char            *target;     File name or heredoc delimiter
    struct s_redir  *next;       Next redirection
}   t_redir;
*/
/**
 * @struct s_cmd
 * @brief Represents a fully parsed command ready for execution.
 *
 */

/*
typedef struct s_cmd
{
    char            **argv;          Command + arguments 
    int             argc;            Number of arguments 
    char            *cmd_path;       Resolved executable path 
    t_redir         *redirs;         Linked list of redirections 
    int             is_builtin;      Whether the command is a builtin 
    struct s_cmd    *next;           Next command in a pipeline 
}   t_cmd;
*/


/*					Parser							*/
t_status			parse(const char *input, t_cmd *cmd);

t_status			init_cmd(t_cmd **cmd);
void				free_cmd(t_cmd **cmd);

#endif
