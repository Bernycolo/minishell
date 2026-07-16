#include "minishell.h"
#include "libft.h"

/**
 * @brief Checks whether a string contains non-printable characters
 *
 * @param str The string to check
 * @return SUCCESS if it is not contains, FAILURE otherwise
 */
t_status	contains_invalid_char(char *str)
{
	while (*str)
	{
		if (!ft_isprint(*str))
			return (SUCCESS);
		str++;
	}
	return (FAILURE);
}

/**
 * @brief Validates the lexical structure of the token list
 *
 * @param tokens The token list to check
 * @return SUCCESS if it is validated, FAILURE otherwise
 */
t_status	lexer_validate(t_token *tokens)
{
	while (tokens)
	{
		if (!tokens->value)
		{
			write(2, "minishell: lexical error: invalid token\n", 40);
			return (FAILURE);
		}
		if (contains_invalid_char(tokens->value))
		{
			write(2, "minishell: lexical error: invalid character\n", 44);
			return (FAILURE);
		}
		if (tokens->type != WORD)
		{
			if (!tokens->next || tokens->next->type != WORD
				|| !tokens->next->value || !tokens->next->value[0])
			{
				print_syntax_error(tokens);
				return (FAILURE);
			}
		}
		tokens = tokens->next;
	}
	return (SUCCESS);
}
