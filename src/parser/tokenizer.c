#include "minishell.h"

/**
 * @brief Creates a new token object
 *
 * @param value The value of the new token
 * @param token_type The type of the new token
 * @return A pointer to the newly created token, or NULL if allocation fails
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
 * @brief Adds a token object to the end of a list
 *
 * @param list A pointer to the head of the token list
 * @param new The new token to add
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
	{
		token_value = malloc(3);
		if (!token_value)
			return ;
		ft_strlcpy(token_value, value, 3);
		token = new_token(token_value, type);
		if (!token)
		{
			free(token_value);
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
			free(token_value);
			return ;
		}
	}
	else if (type == WORD)
	{
		token_value = ft_strdup(value);
		token = new_token(token_value, WORD);
		if (!token)
		{
			free (token_value);
			return ;
		}
	}
	add_token(list, token);
}

/**
 * @brief Skips spaces in a string
 *
 * @param input The input string
 * @param i A pointer to the current index
 */
void	skip_spaces(const char *input, int *i)
{
	while (input && input[*i] == ' ')
		*i += 1;
}

/**
 * @brief Checks if the character at the given index is an operator
 *
 * @param input The input string
 * @param i The current index to check
 * @return SUCCESS if it is an operator, FAILURE otherwise
 */
t_status	is_op(const char *input, int i)
{
	if (input[i] == '<' || input[i] == '>' || input[i] == '|')
		return (SUCCESS);
	return (FAILURE);
}

/**
 * @brief Determines the type of the operator at the given index
 *
 * @param input The input string
 * @param i A pointer to the current index (will be updated)
 * @return The determined token type
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
 * @brief Returns the string representation of a specific operator
 *
 * @param type The token type of the operator
 * @return A string literal representing the operator
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
 * @brief Returns the word to create a new token in quotes
 * 
 * @param input The input string
 * @param i A pointer to the current index (will be updated)
 * @return The string to tokenize
 */
char	*read_quoted(const char *input, int *i)
{
	char	quote;
	int		start;
	char	*result;

	quote = input[*i];
	start = *i;
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
	if (input[*i] != quote)
		return (NULL);
	(*i)++;
	result = ft_substr(input, start, *i - start);
	return (result);
}
/**
 * @brief Returns the word to create a new token
 * 
 * @param input The input string
 * @param i A pointer to the current index (will be updated)
 * @return The string to tokenize 
 */
char	*read_word(const char *input, int *i)
{
	int		start;
	char	*word;
	char	*tmp;
	char	*join;

	word = NULL;
	if (input[*i] && input[*i] != ' ' && !is_op(input, *i))
	{
		if (input[*i] == '"' || input[*i] == '\'')
		{
			tmp = read_quoted(input, i);
			if (!tmp)
				return (NULL);
		}
		else
		{
			start = *i;
			while (input[*i] && input[*i] != ' ' && !is_op(input, *i)
				&& input[*i] != '"' && input[*i] != '\'')
				(*i)++;
			tmp = ft_substr(input, start, *i - start);
		}
		join = ft_strjoin(word, tmp);
		free(tmp);
		free(word);
		word = join;
	}
	return (word);
}

/**
 * @brief Builds a linked list of tokens from the input string
 *
 * @param input The input string to tokenize
 * @return A pointer to the head of the token list
 */
t_token	*tokenizer(const char *input)
{
	t_token			*list;
	t_token_type	type;
	int				i;
	char			*word;

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
			word = read_word(input, &i);
			if (!word)
			{
				ft_printf("bash: unexpected EOF while looking for matching `\"\'\n");
				free_tokenlst(&list);
				return (NULL);
			}
			create_and_add_token(&list, word, WORD);
			free(word);
		}
	}
	return (list);
}
