#include "minishell.h"
// #include "libft.h"

void	builtin_unset(t_shell *shell)
{
	int	i;

	i = 1;
	while (i < shell->cmd->argc)
		env_unset(&shell->env, shell->cmd->arg[i++]);
}


/*
static void	ft_eraser(char *name, t_env *ptr);
static void	del_variable(t_env *node);

void	ft_unset(t_shell *info)
{
	t_env	*ptr;
	int		i;

	i = 0;
	if (!info->cmd->arg[i])
		return ;
	info->last_status = 0;
	while (info->cmd->arg[++i])
	{
		ptr = info->env;
		if (!ptr)
			return ;
		ft_eraser(info->cmd->arg[i], ptr);
	}
}

static void	ft_eraser(char *name, t_env *ptr)
{
	if (!ft_strcmp(name, ptr->next->key))
		return ;
	while (ptr && ptr->next)
	{
		if (!ft_strcmp(name, ptr->next->key))
		{
			del_variable(ptr->next);
			ptr->next = ptr->next->next;
			return ;
		}
		ptr = ptr->next;
	}
}

static void	del_variable(t_env *node)
{
	ft_memfree(node->key);
	ft_memfree(node->value);
	ft_memfree(node);
}

*/