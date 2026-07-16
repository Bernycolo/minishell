#ifndef CMD_H
# define CMD_H

# include "structs.h"

/**
 * @enum e_pstate
 * @brief Represents the internal states of the parser
 * 
 */
typedef enum e_pstate
{
	PS_START,
	PS_WORD,
	PS_REDIR,
	PS_AFTER_REDIR,
	PS_PIPE
}					t_pstate;

/**
 * @struct s_redir
 * @brief Represents a single redirection attached to a command.
 *
 */
typedef struct s_redir
{
	t_token_type	type;
	char			*target;
	bool			quoted;
	struct s_redir	*next;
}					t_redir;

/**
 * @struct s_cmd
 * @brief Represents a node in the parsed command list
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

t_status			new_cmd(t_cmd **cmd);
void				free_cmd(t_cmd **cmd);
void				print_cmd(t_cmd *cmd);

t_redir				*new_redir(t_token_type type);
void				add_redir(t_cmd *cmd, t_token_type type);

#endif
