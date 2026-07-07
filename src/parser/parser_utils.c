#include "minishell.h"
#include "libft.h"

void	print_syntax_error(t_token *token)
{
	write(2, "minishell: syntax error near unexpected token `", 48);
	write(2, token->value, ft_strlen(token->value));
	write(2, "`\n", 2);
}
