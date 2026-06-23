#ifndef CMD_H
# define CMD_H

# include "structs.h"

/**
 * @struct s_cmd
 * @brief Represents a node in the command linked list
 *
 */
typedef struct s_cmd
{
	char			**arg;
	char			*infile;
	char			*outfile;
	int				append;
	int				is_builtin;
	struct s_cmd	*next;
}					t_cmd;

/*

*/

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
}					t_redir;
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
}					t_cmd;
*/

#endif