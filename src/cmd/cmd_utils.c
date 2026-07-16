#include "minishell.h"

/**
 * @brief Frees the memory used by the redirection list
 * 
 * @param redir A pointer to the head of the redir list 
 */
static void	free_redir(t_redir *redir)
{
	t_redir	*aux;

	while (redir)
	{
		aux = redir->next;
		free(redir->target);
		free(redir);
		redir = aux;
	}
}

/**
 * @brief Frees the memory used by the command list
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
		free(cur->cmd_path);
		free_redir(cur->redirs);
		free(cur);
		cur = next;
	}
	*cmd = NULL;
}

/**
 * @brief Prints the contents of a command node
 * 
 * @param cmd The command object to print
 */
void	print_cmd(t_cmd *cmd)
{
	t_redir	*redir;
	int		i;

	i = 0;
	if (cmd->arg)
	{
		while (cmd->arg[i])
		{
			printf("arg[%i] = %s\n", i, cmd->arg[i]);
			i++;
		}
	}
	redir = cmd->redirs;
	if (redir)
	{
		i = 0;
		while (redir)
		{
			printf("%d{%s} is quoted: %d\n",
				redir->type, redir->target, redir->quoted);
			redir = redir->next;
		}
	}
	if (cmd->next)
		print_cmd(cmd->next);
}
