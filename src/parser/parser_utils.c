#include "minishell.h"
#include "libft.h"

/**
 * @brief Prints a syntax error in standar error
 *
 * @param token The token of the error
 */
void	print_syntax_error(t_token *token)
{
	if (!token)
		write(2, "minishell: syntax error near unexpected token `newline`\n",
			57);
	else if (!token->value)
	{
		if (token->type == PIPE)
			write(2, "minishell: syntax error near unexpected token `|`", 51);
		else if (token->type == INPUT)
			write(2, "minishell: syntax error near unexpected token `<`", 51);
		else if (token->type == TRUNC)
			write(2, "minishell: syntax error near unexpected token `>`", 51);
		else if (token->type == APPEND)
			write(2, "minishell: syntax error near unexpected token `>>`", 52);
		else if (token->type == HEREDOC)
			write(2, "minishell: syntax error near unexpected token `<<`", 52);
	}
	else
	{
		write(2, "minishell: syntax error near unexpected token `", 48);
		write(2, token->value, ft_strlen(token->value));
		write(2, "`\n", 2);
	}
}
