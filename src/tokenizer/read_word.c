#include "tokenizer.h"
#include "libft.h"

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
 * @brief Returns the word to create a new token in quotes
 * 
 * @param input The input string
 * @param i A pointer to the current index (will be updated)
 * @return The string to tokenize
 */
static char	*read_quoted(const char *input, int *i)
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

	word = NULL;
	if (input[*i] && input[*i] != ' ' && !is_op(input, *i))
	{
		if (input[*i] == '"' || input[*i] == '\'')
			word = read_quoted(input, i);
		else
		{
			start = *i;
			while (input[*i] && input[*i] != ' ' && !is_op(input, *i)
				&& input[*i] != '"' && input[*i] != '\'')
				(*i)++;
			word = ft_substr(input, start, *i - start);
		}
	}
	return (word);
}
