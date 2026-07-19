#include "minishell.h"
#include "libft.h"

/**
 * @brief Initializes a shell struct
 *
 * @param shell A pointer to the shell struct
 * @param envp The system environment variables
 * @return The prompt of the shell
 */
char	*init_shell(t_shell *shell, char **envp)
{
	shell->env = NULL;
	shell->tokens = NULL;
	shell->cmd = NULL;
	shell->last_status = 0;
	shell->running = 1;
	env_init(&shell->env, envp);
	printf("\033[3J\033[2J\033[H");
	printf("Welcome to minishell!\n");
	return (ft_strjoin(SOFT_YELLOW "minishell" RESET " % ", GRAY));
}

/**
 * @brief Frees the memory space occupied by environment and command list
 *
 * @param shell A pointer to the shell struct
 */
void	end_shell(t_shell *shell)
{
	free_env(&shell->env);
	free_cmd(&shell->cmd);
}
