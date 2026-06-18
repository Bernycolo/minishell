#include "minishell.h"

/**
 * @brief Initializes a struct cmd
 *
 * @param cmd Struct to inicializate
 * @return t_status SUCCESS if it is inicializated, FAILURE otherwise
 */
t_status	init_cmd(t_cmd **cmd)
{
	*cmd = malloc(sizeof(t_cmd));
	if (!*cmd)
		return (FAILURE);
	(*cmd)->arg = NULL;
	(*cmd)->infile = NULL;
	(*cmd)->outfile = NULL;
	(*cmd)->append = 0;
	(*cmd)->is_builtin = 0;
	(*cmd)->next = NULL;
	return (SUCCESS);
}

/**
 * @brief Frees the memory space occupied by a command list
 *
 * @param cmd A pointer to the head of the command list
 */
void	free_cmd(t_cmd **cmd)
{
	t_cmd	*cur;
	t_cmd	*next;
	int		i;

	if (!cmd || !*cmd)
		return ;
	cur = *cmd;
	while (cur)
	{
		next = cur->next;
		if (cur->arg)
		{
			i = 0;
			while (cur->arg[i])
				free(cur->arg[i++]);
			free(cur->arg);
		}
		free(cur->infile);
		free(cur->outfile);
		free(cur);
		cur = next;
	}
	*cmd = NULL;
}
