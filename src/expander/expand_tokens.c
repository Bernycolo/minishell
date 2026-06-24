/* Recorre la lista de tokens y expande solo los WORD. */

#include "minishell.h"

char	*expand_word(char *value, t_env *env, int last_status)
{
	int		i;

	i = 0;
	while (value[i])
	{
		if (value[i] == '$')
			expand_variable();
		i++;
	}
}

static t_token	*del_token(t_token **list, t_token *prev, t_token *curr)
{
	t_token	*next;

	if (!list || !*list || !curr)
		return (NULL);
	next = curr->next;
	if (prev == NULL)
		*list = next;
	else
		prev->next = next;
	free (curr->value);
	free (curr);
	return (next);
}

void	expand_tokens(t_token **list, t_env *env, int last_status)
{
	char	*word;
	t_token	*curr;
	t_token	*prev;

	curr = *list;
	prev = NULL;
	while (curr)
	{
		if (curr->type == WORD && !(prev && prev->type == HEREDOC))
		{
			word = expand_word(curr->value, env, last_status);
			if (!word || !word[0])
			{
				curr = del_token(list, prev, curr);
				continue ;
			}
			free (curr->value);
			curr->value = word;
		}
		prev = curr;
		curr = curr->next;
	}
}
