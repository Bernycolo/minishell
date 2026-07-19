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

/**
 * @brief Compares two strings
 * 
 * @param s1 The string one
 * @param s2 The string two
 * @return Returns an integer indicating the result of the comparison
 * 
 * - 0, if the s1 and s2 are equal
 * 
 * - a negative value if s1 is less than s2
 * 
 * - a positive value if s1 is greater than s2
 */
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s1[i])
		return (s1[i] - s2[i]);
	return (0);
}

/**
 * @brief Joins two strings and frees the allocated memory
 *
 * @param s1 The string one
 * @param s2 The string two
 * @return The join of the two strings
 */
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (join);
}

void	free_mem(void *ptr)
{
	if (!ptr)
		return ;
	free(ptr);
	ptr = NULL;
}
