#include "minishell.h"

int	op_count(const char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input && input[i])
	{
		if (input[i] == '>' && input[i+1] && input[i+1] == '>')
		{
			count++;
			i += 2;
		}
		else if (input[i] == '<' && input[i+1] && input[i+1] == '<')
		{
			count++;
			i += 2;
		}
		else if (ft_strchr("|<>", input[i]))
			count++;
		i++;
	}
	return (count);
}

t_status	parse(const char *input, t_cmd *cmd)
{
	char	**str;
	int	i;
	
	ft_printf("operadores: %d\n", op_count(input));
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
