#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
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

# define BLUE "\033[34m" // azul
# define GRAY "\033[37m" // gris
# define RESET "\033[0m"
# define SOFT_YELLOW "\033[38;5;229m" // amarillo pastel
# define WARM_GRAY "\033[38;5;245m"   // gris cálido

typedef enum e_status
{
	FAILURE,
	SUCCESS
}					t_status;

typedef enum e_token_type
{
	WORD,
	EMPTY,
	CMD,
	ARG,
	TRUNC,
	APPEND,
	INPUT,
	HEREDOC,
	PIPE,
	END
}					t_token_type;

typedef struct s_cmd // Estructura para el comando parseado
{
	char **arg;         // argumentos del comando
	char *infile;       // redirección de entrada
	char *outfile;      // redirección de salida
	int append;         // si es >> o >
	int is_builtin;     // si es builtin
	struct s_cmd *next; // siguiente comando del pipe
}					t_cmd;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env		*next;
}					t_env;

/*							Parser							*/
t_status			parse(const char *input, t_cmd *cmd);
t_status			init_cmd(t_cmd **cmd);
t_token				*new_token(char *value, t_token_type token_type);
void				add_token(t_token **list, t_token *new);
t_token				*tokenizer(const char *input);

void				free_tokenlst(t_token **token_lst);
void				free_cmd(t_cmd **cmd);
void				free_env(t_env **env);
/*							Environment							*/
void	env_init(t_env **env, char **envp);


#endif
