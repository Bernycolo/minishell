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
