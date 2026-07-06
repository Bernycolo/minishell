#ifndef SHELL_H
# define SHELL_H

# include "structs.h"

/**
 * @struct s_shell
 * @brief Global status of minishell
 *
 * Contains the environment, tokens, CMD and the exit status
 *
 */
typedef struct s_shell
{
	t_env	*env;
	t_token	*tokens;
	t_cmd	*cmd;
	int		last_status;
	int		running;
}			t_shell;

char				*init_shell(t_shell *shell, char **envp);
void				end_shell(t_shell *shell);

#endif
