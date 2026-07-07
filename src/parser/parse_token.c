#include "minishell.h"
#include "libft.h"

int	count_arg(char **arg)
{
	int	i;

	i = 0;
	while (arg && arg[i])
		i++;
	return (i);
}

char	**add_arg(t_cmd *cmd, char *value)
{
	int		n_args;
	int		i;
	char	**new_arg;

	n_args = count_arg(cmd->arg);
	new_arg = malloc(sizeof(char *) * (n_args + 2));
	i = 0;
	if (cmd->arg)
	{
		while (cmd->arg[i])
		{
			new_arg[i] = ft_strdup(cmd->arg[i]);
			i++;
		}
	}
	new_arg[i] = ft_strdup(value);
	new_arg[i + 1] = NULL;
	i = 0;
	while (cmd->arg && cmd->arg[i])
		free(cmd->arg[i++]);
	if (cmd->arg)
		free(cmd->arg);
	return (new_arg);
}
/*
int	count_words(t_token *tokens)
{
	int		count;
	t_token	*curr;

	count = 0;
	curr = tokens;
	while (curr)
	{
		if (curr->type == WORD)
			count++;
		else if (curr->type == PIPE)
			break ;
		curr = curr->next;
	}
	return (count);
}

t_status	fill_cmd(t_shell **shell)
{
t_token	*curr;
t_pstate	state;

curr = (*shell)->tokens;
state = PS_START;
while (curr)
{
if (curr->type == WORD)
{
(*shell)->cmd->arg = add_arg((*shell)->cmd, curr->value);
(*shell)->cmd->argc++;
}
else if (curr->type == INPUT || curr->type == TRUNC
|| curr->type == APPEND || curr->type == HEREDOC)
{
(*shell)->cmd->redirs = new_redir(curr->type,
ft_strdup(curr->next->value));
curr = curr->next;
}
curr = curr->next;
}
return (SUCCESS);
}
*/

t_status	manage_start(t_token *tokens, t_cmd **cmds, t_pstate *state)
{
	if (tokens->type == WORD)
	{
		(*cmds)->arg = add_arg(*cmds, tokens->value);
		(*cmds)->argc++;
		*state = PS_WORD;
		return (SUCCESS);
	}
	else if (tokens->type == TRUNC || tokens->type == INPUT
		|| tokens->type == APPEND || tokens->type == HEREDOC)
	{
		(*cmds)->redirs = new_redir(tokens->type);
		*state = PS_REDIR;
		return (SUCCESS);
	}
	return (FAILURE);
}

t_status	manage_word(t_token *tokens, t_cmd **cmds, t_pstate *state)
{
	t_cmd	*new;

	if (tokens->type == WORD)
	{
		(*cmds)->arg = add_arg(*cmds, tokens->value);
		(*cmds)->argc++;
	}
	else if (tokens->type == TRUNC || tokens->type == INPUT
		|| tokens->type == APPEND || tokens->type == HEREDOC )
		{
			(*cmds)->redirs = new_redir(tokens->type);
			*state = PS_REDIR;
		}
	else if (tokens->type == PIPE)
	{
		new_cmd(&new);
		(*cmds)->next = new;
		*cmds = new;
		*state = PS_PIPE;
	}
	else
		return (FAILURE);
	return (SUCCESS);
}

t_status	manage_redir(t_token *tokens, t_cmd **cmds, t_pstate *state)
{
	if (tokens->type == WORD)
	{
		(*cmds)->redirs->target = ft_strdup(tokens->value);
		*state = PS_AFTER_REDIR;
		return (SUCCESS);
	}
	printf("parse error near '%s", tokens->value);
	return (FAILURE);
}

t_status	manage_after_redir(t_token *tokens, t_cmd **cmds, t_pstate *state)
{
	if (tokens->type == TRUNC || tokens->type == INPUT
		|| tokens->type == APPEND || tokens->type == HEREDOC)
	{
		(*cmds)->redirs = new_redir(tokens->type);
		*state = PS_REDIR;
	}
	else if (tokens->type == PIPE)
		*state = PS_PIPE;
	else if (tokens->type == WORD)
	{
		(*cmds)->arg = add_arg(*cmds, tokens->value);
		(*cmds)->argc++;
		*state = PS_WORD;
	}
	return (SUCCESS);
}

t_status	manage_pipe(t_token *tokens, t_cmd **cmds, t_pstate *state)
{
	t_cmd	*new;

	if (tokens->type == WORD)
	{
		new_cmd(&new);
		(*cmds)->next = new;
		*cmds = new;
		new->arg = add_arg(new, tokens->value);
		new->argc = 1;
		*state = PS_WORD;
		return (SUCCESS);
	}
		if (tokens->type == TRUNC || tokens->type == INPUT
		|| tokens->type == APPEND || tokens->type == HEREDOC)
	{
		new_cmd(&new);
		(*cmds)->next = new;
		*cmds = new;
		new->redirs = new_redir(tokens->type);
		*state = PS_REDIR;
		return (SUCCESS);
	}
	return (FAILURE);
}

t_status	fill_cmd(t_shell **shell)
{
	t_pstate	state;
	t_status	result_state;
	t_token		*tokens;
	t_cmd		*cmds;

	tokens = (*shell)->tokens;
	cmds = (*shell)->cmd;
	state = PS_START;
	result_state = SUCCESS;
	while (tokens && result_state)
	{
		if (state == PS_START)
			result_state = manage_start(tokens, &cmds, &state);
		else if (state == PS_WORD)
			result_state = manage_word(tokens, &cmds, &state);
		else if (state == PS_REDIR)
			result_state = manage_redir(tokens, &cmds, &state);
		else if (state == PS_AFTER_REDIR)
			result_state = manage_after_redir(tokens, &cmds, &state);
		else
			result_state = manage_pipe(tokens, &cmds, &state);
		tokens = tokens->next;
	}
	return (result_state);
}

t_cmd	*parse_token(t_shell *shell)
{
	new_cmd(&shell->cmd);
	if (!fill_cmd(&shell))
	{
		free_tokenlst(&shell->tokens);
		free_cmd(&shell->cmd);
//		printf("Syntax error!.\n");
		return (NULL);
	}
	free_tokenlst(&shell->tokens);
	return (shell->cmd);
}
