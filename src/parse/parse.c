#include "minishell.h"

void	tokenize(const char *input)
{
	int	i;
	int	sep;

	i = 0;
	sep = 0;
	while (input && input[i])
	{
		if (ft_strchr("|<>;", input[i]))
			sep++;
		i++;
	}
	ft_printf("long i: %d\n", i);
	ft_printf("long sep: %d\n", sep);
}

t_status	parse(const char *input, t_cmd *cmd)
{
	char	**str;
	int	i;

	tokenize(input);
	str = ft_split(input, ' ');
	if (cmd->arg)
	{
		i = 0;
		while (cmd->arg[i])
			free(cmd->arg[i++]);
		free(cmd->arg);
	}
	cmd->arg = str;
	return (SUCCESS);
}
