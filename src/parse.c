#include "minishell.h"

t_status	parse(const char *input, t_cmd *cmd)
{
	cmd->arg = ft_split(input,  ' ');
	return (SUCCESS);
}
