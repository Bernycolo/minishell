#include "minishell.h"
#include "libft.h"

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

t_status	lexer_validate(t_token *tokens)
{
	while (tokens)
	{
		if (!tokens->value && tokens->type == WORD)
		{
			write(2, "minishell: lexical error: invalid token\n", 40);
			return (FAILURE);
		}
		if (!tokens->value)
		{
			write(2, "minishell: lexical error: invalid token\n", 40);
			return (FAILURE);
		}
		if (tokens->value && contains_invalid_char(tokens->value))
		{
			write(2, "minishell: lexical error: invalid character\n", 44);
			return (FAILURE);
		}
		if (tokens->type != WORD)
		{
			if (!tokens->next || tokens->next->type != WORD || !tokens->next->value[0])
			{
				write(2, "minishell: syntax error near unexpected token `newline`\n", 57);
				return (FAILURE);
			}
		}
		tokens = tokens->next;
	}
	return (SUCCESS);
}
