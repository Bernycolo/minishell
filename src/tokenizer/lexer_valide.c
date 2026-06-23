#include "tokenizer.h"
#include <stddef.h>

t_status	check_first_token(t_token *token)
{
	if (token->type == PIPE || token->type == INPUT || token->type == TRUNC
		|| token->type == HEREDOC || token->type == APPEND)
		return (FAILURE);
	return (SUCCESS);
}

t_status	check_pipe(t_token *token)
{
	if (token->type == PIPE && token->next == NULL)
		return (FAILURE);
	if (token->type == PIPE && token->next)
	{
		if (token->next->type == PIPE || token->next->type == INPUT
			|| token->next->type == TRUNC || token->next->type == HEREDOC
			|| token->next->type == APPEND)
			return (FAILURE);
	}
	return (SUCCESS);
}

t_status	check_redir(t_token *token)
{
	if (token->type == INPUT || token->type == TRUNC || token->type == HEREDOC
		|| token->type == APPEND)
	{
		if (token->next->type == PIPE || token->next->type == INPUT
			|| token->next->type == TRUNC || token->next->type == HEREDOC
			|| token->next->type == APPEND)
			return (FAILURE);
	}
	return (SUCCESS);
}

t_status	check_op_secuence(t_token *token)
{
	(void)*token;
	return (SUCCESS);
}

t_status	check_last_token(t_token *token)
{
	if (token->type == PIPE || token->type == INPUT || token->type == TRUNC
		|| token->type == HEREDOC || token->type == APPEND)
		return (FAILURE);
	return (SUCCESS);
}

t_status	lexer_validate(t_token *token)
{
	if (!check_first_token(token))
		return (FAILURE);
	while (token && token->next)
	{
		if (!check_pipe(token))
			return (FAILURE);
		if (!check_redir(token))
			return (FAILURE);
		if (!check_op_secuence(token))
			return (FAILURE);
		token = token->next;
	}
	if (!check_last_token(token))
		return (FAILURE);
	return (SUCCESS);
}
