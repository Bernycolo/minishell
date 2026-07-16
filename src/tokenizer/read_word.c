#include "minishell.h"
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
 * @brief Reads a quoted word and returns it as a token fragment
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
 * @brief Reads an unquoted word and returns it as a token fragment
 * 
 * @param input The input string
 * @param i A pointer to the current index (wil be updated)
 * @return The string to tokenize
 */
static char	*read_unquoted(const char *input, int *i)
{
	int		start;
	char	*result;

	start = *i;
	while (input[*i] && input[*i] != ' ' && !is_op(input, *i)
		&& input[*i] != '"' && input[*i] != '\'')
		(*i)++;
	result = ft_substr(input, start, *i - start);
	return (result);
}

/**
 * @brief Joins two strings and frees the allocated memory
 *
 * @param s1 The string one
 * @param s2 The string two
 * @return The join of the two strings
 */
char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*join;

	join = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (join);
}

/**
 * @brief Reads a word from the input and returns it
 *
 * @param input The input string
 * @param i A pointer to the current index (will be updated)
 * @return The string to tokenize
 */
char	*read_word(const char *input, int *i)
{
	char	*word;
	char	*tmp;

	word = ft_strdup("");
	if (!word)
		return (NULL);
	while (input[*i] && input[*i] != ' ' && !is_op(input, *i))
	{
		if (input[*i] == '"' || input[*i] == '\'')
		{
			tmp = read_quoted(input, i);
			if (!tmp)
				return (free(word), NULL);
			word = ft_strjoin_free(word, tmp);
		}
		else
		{
			tmp = read_unquoted(input, i);
			if (!tmp)
				return (free(word), NULL);
			word = ft_strjoin_free(word, tmp);
		}
	}
	return (word);
}
