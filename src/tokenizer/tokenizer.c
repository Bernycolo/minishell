#include "minishell.h"

/**
 * @brief Skips spaces in a string
 *
 * @param input The input string
 * @param i A pointer to the current index
 */
static void	skip_spaces(const char *input, int *i)
{
	while (input && input[*i] == ' ')
		*i += 1;
}

/**
 * @brief Determines the type of the operator at the given index
 *
 * @param input The input string
 * @param i A pointer to the current index (will be updated)
 * @return The determined token type
 */
static t_token_type	type_op(const char *input, int *i)
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
static char	*value_op(t_token_type type)
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
 * @brief Create a token node object
 *
 * @param input The string from to extract the token
 * @param list The list of tokens
 * @param i A pointer to the current index (will be updated)
 * @return SUCCESS if it is created the token, FAILURE otherwise
 */
t_status	create_token_node(const char *input, t_token **list, int *i)
{
	t_token_type	type;
	char			*word;

	if (is_op(input, *i))
	{
		type = type_op(input, i);
		create_and_add_token(list, value_op(type), type);
	}
	else
	{
		word = read_word(input, i);
		if (!word)
		{
			write(2, "minishell: unexpected EOF while"
				" looking for matching `\"\'\n",
				57);
			free_tokenlst(list);
			return (FAILURE);
		}
		create_and_add_token(list, word, WORD);
		free(word);
	}
	return (SUCCESS);
}

/**
 * @brief Builds a linked list of tokens from the input string
 *
 * @param input The input string to tokenize
 * @return A pointer to the head of the token list
 */
t_token	*tokenizer(const char *input)
{
	t_token	*list;
	int		i;

	list = NULL;
	i = 0;
	while (input && input[i])
	{
		skip_spaces(input, &i);
		if (input[i])
		{
			if (!create_token_node(input, &list, &i))
				return (NULL);
		}
	}
	return (list);
}
