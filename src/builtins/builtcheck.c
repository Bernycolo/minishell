#include "minishell.h"
#include "libft.h"

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
	//	printf("Is export.\n");
		builtin_export(shell);
	else if (!ft_strncmp(shell->cmd->arg[0], "unset", 5))
		builtin_unset(shell);
	else if (!ft_strcmp(shell->cmd->arg[0], "env"))
		builtin_env(shell);
	else if (!ft_strcmp(shell->cmd->arg[0], "exit"))
		builtin_exit(shell);
}