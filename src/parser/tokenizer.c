#include "minishell.h"

/**
 * @brief Create token object
 * 
 * @param value 
 * @param token_type 
 * @return t_token* 
 */
t_token	*new_token(char *value, t_token_type token_type)
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
 * @brief Add token object
 * 
 * @param list 
 * @param new 
 */
void	add_token(t_token **list, t_token *new)
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
 * @brief Create a and add token object
 * 
 * @param list 
 * @param value 
 * @param type 
 */
void	create_and_add_token(t_token **list, const char *value, t_token_type type)
{
	t_token	*token;
	char	*token_value;

	token = NULL;
	token_value = NULL;
	if (type == HEREDOC || type == APPEND)
	{
		token_value = malloc(3);
		if (!token_value)
			return ;
		ft_strlcpy(token_value, value, 3);
		token = new_token(token_value, type);
		if (!token)
		{
			free (token_value);
			return ;
		}
	}
	else if (type == PIPE || type == TRUNC || type == INPUT)
	{
		token_value = malloc(2);
		if (!token_value)
			return ;
		ft_strlcpy(token_value, value, 2);
		token = new_token(token_value, type);
		if (!token)
		{
			free (token_value);
			return ;
		}
	}
	else if (type == WORD)
	{
		token = new_token(ft_strdup(value), WORD);
		if (!token)
			return ;
	}
	add_token(list, token);
}

void	skip_spaces(const char *input, int *i)
{
	while (input && input[*i] == ' ')
		*i += 1;
}

/**
 * @brief Check if the input is an operator
 * 
 * @param input 
 * @param i 
 * @return t_status 
 */
t_status	is_op(const char *input, int i)
{
	if (input[i] == '<' || input[i] == '>' || input[i] == '|')
		return (SUCCESS);
	return (FAILURE);
}

/**
 * @brief returns the type of the specified operator
 * 
 * @param input 
 * @param i 
 * @return t_token_type 
 */
t_token_type	type_op(const char *input, int *i)
{
	if (input[*i] == '<' && input[*i + 1] && input[*i + 1] == '<')
	{
		*i += 2;
		return (HEREDOC);
	}
	else if (input[*i] == '>' && input[*i + 1] && input[*i + 1] == '>')
	{
		*i += 2;
		return (APPEND);
	}
	else if (input[*i] == '|')
	{
		*i += 1;
		return (PIPE);
	}
	else if (input[*i] == '<')
	{
		*i += 1;
		return (INPUT);
	}
	else
	{
		*i += 1;
		return (TRUNC);
	}
}

/**
 * @brief Returns the value of the specified operator
 * 
 * @param type 
 * @return char* 
 */
char	*value_op(t_token_type type)
{
	if (type == HEREDOC)
		return ("<<");
	if (type == APPEND)
		return (">>");
	if (type == INPUT)
		return ("<");
	if (type == TRUNC)
		return (">");
	return ("|");
}

/**
 * @brief Build a token's list from the input
 * 
 * @param input 
 * @return t_token* 
 */
t_token	*tokenizer(const char *input)
{
	t_token			*list;
	t_token_type	type;
	int				i;
	int				start;
	int				len_token;
	char	*word;

	list = NULL;
	i = 0;
	while (input && input[i])
	{
		skip_spaces(input, &i);
		if (is_op(input, i))
		{
			type = type_op(input, &i);
			create_and_add_token(&list, value_op(type), type);
		}
		else
		{
			start = i;
			while (input[i] && input[i] != ' ' && !is_op(input, i))
				i++;
			len_token = i  - start;
			word = ft_substr(input, start, len_token);
			if (word)
			{
				create_and_add_token(&list, word, WORD); // crear y añadir token
				free (word);
			}
		}
	}
	return (list);
}
