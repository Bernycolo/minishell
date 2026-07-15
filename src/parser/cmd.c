#include "minishell.h"

/**
 * @brief Initializes a struct cmd
 *
 * @param cmd Struct to inicializate
 * @return t_status SUCCESS if it is inicializated, FAILURE otherwise
 */
t_status	new_cmd(t_cmd **cmd)
{
	*cmd = malloc(sizeof(t_cmd));
	if (!*cmd)
		return (FAILURE);
	(*cmd)->arg = NULL;
	(*cmd)->argc = 0;
	(*cmd)->cmd_path = NULL;
	(*cmd)->redirs = NULL;
	(*cmd)->is_builtin = 0;
	(*cmd)->next = NULL;
	return (SUCCESS);
}

/**
 * @brief Creates a new redir object
 * 
 * @param type The type of the new redir
 * @param target The target of the redirection
 * @return A pointer to the newly creater redir, or NULL if allocation fails
 */
t_redir	*new_redir(t_token_type type)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->type = type;
	redir->quoted = false;
	redir->target = NULL;
	redir->next = NULL;
	return (redir);
}

/**
 * @brief Adds a redirection struct to a command list
 * 
 * @param cmd The command list
 * @param type The redirection type
 */
void	add_redir(t_cmd *cmd, t_token_type type)
{
	t_redir	*new;
	t_redir	*curr;

	new = new_redir(type);
	if (!cmd->redirs)
	{
		cmd->redirs = new;
		return ;
	}
	curr = cmd->redirs;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}

/**
 * @brief Frees the memory space occupied by a redir list
 * 
 * @param redir A pointer to the head of the redir list 
 */
void	free_redir(t_redir *redir)
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
		free(cur->cmd_path);
		free_redir(cur->redirs);
		free(cur);
		cur = next;
	}
	*cmd = NULL;
}

/**
 * @brief Prints the elements of a command object
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
			printf("%d{%s} is quoted: %d\n", redir->type, redir->target, redir->quoted);
			redir = redir->next;
		}
	}
	if (cmd->next)
		print_cmd(cmd->next);
	return ;
}
