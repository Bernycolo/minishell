/* Recorre la lista de tokens y expande solo los WORD. */

#include "tokenizer.h"
#include <stddef.h>

t_token	*expand_word(t_token *token)
{
	int	i;

	i = 0;
	while (token->value[i])
	{
		if (token->value[i] == '$')
			expand_variable(token);
		i++;
	}
}

t_status	expand_tokens(t_token *token)
{
	while (token && token->next)
	{
		if (token->type == WORD)
			expand_word(token);
		token = token->next;
	}
	return (SUCCESS);
}
