#include "minishell.h"
#include "libft.h"

void	builtin_echo(t_shell *msh)
{
	int	i;

	i = 1;
	msh->last_status = 0;
	if (msh->cmd->arg[1] && !ft_strncmp(msh->cmd->arg[1], "-n", 2))
		i++;
	while (msh->cmd->arg[i])
	{
		ft_putstr_fd(msh->cmd->arg[i++], 1);
		if (msh->cmd->arg[i])
			ft_putchar_fd(32, 1);
	}
	if (!(msh->cmd->arg[1] && !ft_strncmp(msh->cmd->arg[1], "-n", 2)))
		ft_putchar_fd(10, 1);
}
