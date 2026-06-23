#ifndef SHELL_H
# define SHELL_H

# include "structs.h"

/**
 * @struct s_shell
 * @brief Global status of minishell
 *
 * Contains the environment, tokens, AST and the exit status
 *
 */
typedef struct s_shell
{
	t_env	*env;
	t_token	*tokens;
	// t_ast	*ast;
	int		last_status;
	int		running;
}			t_shell;

#endif