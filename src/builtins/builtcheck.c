#include "minishell.h"
#include "libft.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	while (s1[i] && s1[i] == s2[i])
		i++;
	if (s1[i])
		return (1);
	return (0);
}

t_status	is_builtin(t_cmd *cmd)
{
	if (!ft_strcmp(cmd->arg[0], "echo") || !ft_strcmp(cmd->arg[0], "cd")
		|| !ft_strcmp(cmd->arg[0], "pwd") || !ft_strcmp(cmd->arg[0], "export")
		|| !ft_strcmp(cmd->arg[0], "unset") || !ft_strcmp(cmd->arg[0], "env")
		|| !ft_strcmp(cmd->arg[0], "exit"))
		return (SUCCESS);
	return (FAILURE);
}

void	ft_builtin(t_shell *shell)
{
	if (!ft_strcmp(shell->cmd->arg[0], "echo"))
		builtin_echo(shell);
	else if (!ft_strcmp(shell->cmd->arg[0], "cd"))
		builtin_cd(shell);
	else if (!ft_strcmp(shell->cmd->arg[0], "pwd"))
		builtin_pwd(shell);
	else if (!ft_strncmp(shell->cmd->arg[0], "export", 6))
		printf("Is export.\n");
	//	builtin_export(shell);
	else if (!ft_strncmp(shell->cmd->arg[0], "unset", 5))
		printf("Is unset.\n");
	//	ft_unset(mycmd);
	else if (!ft_strcmp(shell->cmd->arg[0], "env"))
		builtin_env(shell);
	else if (!ft_strcmp(shell->cmd->arg[0], "exit"))
		builtin_exit(shell);
}