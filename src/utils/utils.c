#include "minishell.h"
#include "libft.h"

/**
 * @brief Initializes a struct cmd
 *
 * @param cmd Struct to inicializate
 * @return t_status SUCCESS if it is inicializated, FAILURE otherwise
 */
t_status	init_cmd(t_cmd **cmd)
{
	*cmd = malloc(sizeof(t_cmd));
	if (!*cmd)
		return (FAILURE);
	(*cmd)->arg = NULL;
	(*cmd)->infile = NULL;
	(*cmd)->outfile = NULL;
	(*cmd)->append = 0;
	(*cmd)->is_builtin = 0;
	(*cmd)->next = NULL;
	return (SUCCESS);
}

/**
 * @brief Frees the memory space occupied by a command list
 *
 * @param cmd A pointer to the head of the command list
 */
void	free_cmd(t_cmd **cmd)
{
	t_cmd	*cur;
	t_cmd	*next;
	int		i;

	if (!cmd || !*cmd)
		return ;
	cur = *cmd;
	while (cur)
	{
		next = cur->next;
		if (cur->arg)
		{
			i = 0;
			while (cur->arg[i])
				free(cur->arg[i++]);
			free(cur->arg);
		}
		free(cur->infile);
		free(cur->outfile);
		free(cur);
		cur = next;
	}
	*cmd = NULL;
}

/**
 * @brief Initializes a shell struct
 * 
 * @param shell A pointer to the shell struct
 * @param envp The system environment variables 
 */
char	*init_shell(t_shell *shell, char **envp)
{
	shell->env = NULL;
	shell->tokens = NULL;
	shell->cmd = NULL;
	shell->last_status = 0;
	shell->running = 1;
	env_init(&shell->env, envp);
	init_cmd(&shell->cmd);
	printf("\033[3J\033[2J\033[H");
	printf("Welcome to minishell!\n");
	return (ft_strjoin(SOFT_YELLOW "minishell" RESET " % ", GRAY));
}

void	end_shell(t_shell *shell)
{
	free_env(&shell->env);
	free_cmd(&shell->cmd);
}
