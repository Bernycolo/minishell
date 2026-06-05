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
	tokenize(input);
	cmd->arg = ft_split(input, ' ');
	return (SUCCESS);
}
