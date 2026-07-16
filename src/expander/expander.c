#include "minishell.h"

/**
 * @brief Deletes the current token from the list
 * 
 * @param list The token's list
 * @param prev The previous token
 * @param curr The token to delete
 * @return The token's list with the token deleted
 */
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

/**
 * @brief Expands the content of the tokens list
 * 
 * @param list The token's list
 * @param env The environment list
 * @param last_status The last exit status returned by the shell
 */
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
			if (!word)
				curr = del_token(list, prev, curr);
			else
			{
				free (curr->value);
				curr->value = word;
			}
		}
		prev = curr;
		curr = curr->next;
	}
}
