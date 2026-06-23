#include "minishell.h"

/**
 * @brief Checks the token's type of the head of the token's list
 * 
 * @param token The token to check
 * @return SUCCESS if the token is not an operator, FAILURE otherwise 
 */
t_status	check_first_token(t_token *token)
{
	if (token->type == PIPE || token->type == INPUT || token->type == TRUNC
		|| token->type == HEREDOC || token->type == APPEND)
		return (FAILURE);
	return (SUCCESS);
}

/**
 * @brief Checks if its a PIPE and the next token  
 * 
 * @param token The token to check
 * @return SUCCESS if the token is a PIPE and the next token is not,
 * FAILURE otherwise 
 */
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

/**
 * @brief 
 * 
 * @param token 
 * @return t_status 
 */
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

/**
 * @brief 
 * 
 * @param token 
 * @return t_status 
 */
t_status	check_last_token(t_token *token)
{
	if (token->type == PIPE || token->type == INPUT || token->type == TRUNC
		|| token->type == HEREDOC || token->type == APPEND)
		return (FAILURE);
	return (SUCCESS);
}

/**
 * @brief 
 * 
 * @param token 
 * @return t_status 
 */
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
		token = token->next;
	}
	if (!check_last_token(token))
		return (FAILURE);
	return (SUCCESS);
}
