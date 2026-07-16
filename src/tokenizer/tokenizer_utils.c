#include "minishell.h"
#include "libft.h"

/**
 * @brief Creates a new token object
 *
 * @param value The value of the new token
 * @param token_type The type of the new token
 * @return A pointer to the newly created token, or NULL if allocation fails
 */
static t_token	*new_token(char *value, t_token_type token_type)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = token_type;
	token->next = NULL;
	return (token);
}

/**
 * @brief Adds a token object to the end of a list
 *
 * @param list A pointer to the head of the token list
 * @param new The new token to add
 */
static void	add_token(t_token **list, t_token *new)
{
	t_token	*aux;

	if (!list)
		return ;
	if (*list)
	{
		aux = *list;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
	else if (new)
		*list = new;
}

/**
 * @brief Frees the memory space occupied by a token list
 *
 * @param token_lst A pointer to the head of the token list
 */
void	free_tokenlst(t_token **token_lst)
{
	t_token	*aux;
	t_token	*tmp;

	if (!token_lst || !*token_lst)
		return ;
	aux = *token_lst;
	while (aux)
	{
		tmp = aux->next;
		free(aux->value);
		free(aux);
		aux = tmp;
	}
	*token_lst = NULL;
}

/**
 * @brief Creates an operator object
 *
 * @param type_op The number of characters of the operator
 * @param type The type of the operator
 * @param value The value of the operator read from the input
 * @return t_token* The new operator token created
 */
static t_token	*create_op(int type_op, t_token_type type, const char *value)
{
	t_token	*token;
	char	*token_value;

	token_value = NULL;
	if (type_op == 2)
	{
		token_value = malloc(3);
		if (!token_value)
			return (NULL);
		ft_strlcpy(token_value, value, 3);
	}
	else if (type_op == 1)
	{
		token_value = malloc(2);
		if (!token_value)
			return (NULL);
		ft_strlcpy(token_value, value, 2);
	}
	token = new_token(token_value, type);
	if (!token)
	{
		free(token_value);
		return (NULL);
	}
	return (token);
}

/**
 * @brief Creates a new token and adds it to the token list
 *
 * @param list A pointer to the head of the token list
 * @param value The value of the new token
 * @param type The type of the new token
 */
void	create_and_add_token(t_token **list, const char *value,
		t_token_type type)
{
	t_token	*token;
	char	*token_value;

	token = NULL;
	token_value = NULL;
	if (type == HEREDOC || type == APPEND)
		token = create_op(2, type, value);
	else if (type == PIPE || type == TRUNC || type == INPUT)
		token = create_op(1, type, value);
	else if (type == WORD)
	{
		token_value = ft_strdup(value);
		token = new_token(token_value, WORD);
	}
	if (!token)
	{
		if (token_value)
			free(token_value);
		return ;
	}
	add_token(list, token);
}
