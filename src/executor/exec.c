#include "minishell.h"

void	classify_cmd(t_cmd **cmd)
{
	t_cmd	*aux;

	aux = *cmd;
	while (aux)
	{
		if (aux->argc == 0)
			aux->is_builtin = 0;
		else
			aux->is_builtin = is_builtin(aux);
		aux = aux->next;
	}
}

t_status	prepare_redirections(t_shell *shell)
{
	(void)shell;
	return (SUCCESS);
}

void	execute_single(t_shell *shell)
{
	classify_cmd(&shell->cmd);
	if (shell->cmd->is_builtin)
		ft_builtin(shell);
	return ;
}

void	execute_pipeline(t_shell *shell)
{
	(void)shell;
	return ;
}

void	executor(t_shell *shell)
{
	if (!shell->cmd)
	{
		printf("no command\n");
		return ;
	}
	if (!prepare_redirections(shell))
		return ;
	if (!shell->cmd->next)
		execute_single(shell);
	else
		execute_pipeline(shell);
}
