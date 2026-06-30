#ifndef CMD_H
# define CMD_H

# include "structs.h"

/**
 * @struct s_redir
 * @brief Represents a single redirection associated with a command.
 *
 */

typedef struct s_redir
{
	t_token_type	type;
	char			*target;
	struct s_redir	*next;
}					t_redir;

/**
 * @struct s_cmd
 * @brief Represents a node in the command linked list
 *
 */
typedef struct s_cmd
{
	char			**arg;
	int				argc;
	char			*cmd_path;
	t_redir			*redirs;
	int				is_builtin;
	struct s_cmd	*next;
}					t_cmd;

#endif
