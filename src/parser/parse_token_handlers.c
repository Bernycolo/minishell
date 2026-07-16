#include "minishell.h"
#include "parse_token.h"
#include "libft.h"

/**
 * @brief Process the startup token
 * 
 * @param tokens The token to process
 * @param cmds The command to complete
 * @param state The state of the process
 * @return SUCCESS if it is processed, FAILURE otherwise
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
		add_redir(*cmds, tokens->type);
		*state = PS_REDIR;
		return (SUCCESS);
	}
	print_syntax_error(tokens);
	return (FAILURE);
}

/**
 * @brief Process a token type WORD
 * 
 * @param tokens The token to process
 * @param cmds The command list
 * @param state The state of the process
 * @return SUCCESS if it is processed, FAILURE otherwise
 */
t_status	manage_word(t_token *tokens, t_cmd **cmds, t_pstate *state)
{
	t_cmd	*new;

	if (tokens->type == WORD)
	{
		(*cmds)->arg = add_arg(*cmds, tokens->value);
		(*cmds)->argc++;
	}
	else if (is_redir_token(tokens->type))
	{
		add_redir(*cmds, tokens->type);
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
	{
		print_syntax_error(tokens);
		return (FAILURE);
	}
	return (SUCCESS);
}

/**
 * @brief Process a redirection token
 * 
 * @param tokens The token to process
 * @param cmds The command list
 * @param state The state of the process
 * @return SUCCESS if it is processed, FAILURE otherwise
 */
t_status	manage_redir(t_token *tokens, t_cmd **cmds, t_pstate *state)
{
	t_redir	*last;

	if (tokens->type == WORD)
	{
		last = (*cmds)->redirs;
		if (!last)
			return (FAILURE);
		while (last && last->next)
			last = last->next;
		if (last->type != HEREDOC)
			last->target = ft_strdup(tokens->value);
		else
		{
			last->quoted = is_quoted(tokens->value);
			last->target = remove_quotes(tokens->value);
		}
		*state = PS_AFTER_REDIR;
		return (SUCCESS);
	}
	print_syntax_error(tokens);
	return (FAILURE);
}

/**
 * @brief Process the token after a redirection
 * 
 * @param tokens The token to process
 * @param cmds The command list
 * @param state The state of the process
 * @return SUCCESS if it is processed, FAILURE otherwise 
 */
t_status	manage_after_redir(t_token *tokens, t_cmd **cmds, t_pstate *state)
{
	if (tokens->type == TRUNC || tokens->type == INPUT || tokens->type == APPEND
		|| tokens->type == HEREDOC)
	{
		add_redir(*cmds, tokens->type);
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
	else
	{
		print_syntax_error(tokens);
		return (FAILURE);
	}
	return (SUCCESS);
}

/**
 * @brief Process a PIPE token
 * 
 * @param tokens The token to process
 * @param cmds The command list
 * @param state The state of the process
 * @return SUCCESS if it is processed, FAILURE otherwise
 */
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
	if (tokens->type == TRUNC || tokens->type == INPUT || tokens->type == APPEND
		|| tokens->type == HEREDOC)
	{
		new_cmd(&new);
		(*cmds)->next = new;
		*cmds = new;
		add_redir(new, tokens->type);
		*state = PS_REDIR;
		return (SUCCESS);
	}
	print_syntax_error(tokens);
	return (FAILURE);
}
