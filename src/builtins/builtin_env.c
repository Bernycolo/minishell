#include "minishell.h"
#include "libft.h"

void	builtin_env(t_shell *msh)
{
	t_env	*tmp;

	if (msh->cmd->argc > 1)
	{
		printf("env: %s: No such file or directory\n", msh->cmd->arg[1]);
		msh->last_status = 127;
		return ;
	}
	tmp = msh->env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "_\0", 2))
			printf("_=/usr/bin/env\n");
		else
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	msh->last_status = 0;
}