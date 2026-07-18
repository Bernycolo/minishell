#include "minishell.h"
#include "libft.h"

static int	check_exit_args(t_shell *msh)
{
	int	i;

	if (msh->cmd->argc > 2)
		return (1);
	if (msh->cmd->arg[1])
	{
		i = -1;
		while (msh->cmd->arg[1][++i])
		{
			if (!ft_isdigit(msh->cmd->arg[1][i]))
			{
				printf("exit: %s: numeric argument required\n",
					msh->cmd->arg[1]);
				return (2);
			}
		}
		return (ft_atoi(msh->cmd->arg[1]));
	}
	return (0);
}

void	builtin_exit(t_shell *msh)
{
	ft_putendl_fd("exit", 2);
	msh->last_status = check_exit_args(msh);
	if (msh->last_status == 0)
		exit(msh->last_status);
	ft_putendl_fd("exit: too many arguments", 2);
}
