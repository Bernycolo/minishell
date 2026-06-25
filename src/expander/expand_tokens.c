/* Recorre la lista de tokens y expande solo los WORD. */

#include "minishell.h"

/**
 * @brief Extracts the text between single quotes
 * 
 * @param value The text with single quotes
 * @param index A pointer to an index
 * @return The extracted text
 */
char	*extract_single_quoted(char *value, int *index)
{
	char	*result;

	return (result);
}

/**
 * @brief Extracts the text between double quotes
 * 
 * @param value The text with double quotes
 * @param index A pointer to an index
 * @return The extracted text
 */
char	*extract_double_quoted(char *value, int *index)
{
	char	*result;

	return (result);
}

/**
 * @brief Expands the value of a environment variable
 * 
 * @param value The key of the variable
 * @param index A pointer to an index
 * @param env The environment list
 * @param last_status The last state returned by the system
 * @return The expanded text 
 */
char	*expand_variable(char *value, int *index, t_env *env, int last_status)
{
	char	*result;

	return (result);
}

/**
 * @brief Extracts the plain text until find quotation marks or $
 * 
 * @param value The source text
 * @param index A pointer to an index
 * @return The extracted text
 */
char	*extract_plain_text(char *value, int *index)
{
	char	*result;

	return (result);
}

/**
 * @brief 
 * 
 * @param value 
 * @param env 
 * @param last_status The last state returned by the system
 * @return char* 
 */
char	*expand_word(char *value, t_env *env, int last_status)
{

	int		i;
	char	*result;
	char	*fragment;

	result = ft_strdup("");
	i = 0;
	while (value[i])
	{
		if (value[i] == '\'')
			fragment = extract_single_quoted(value, &i);
		else if (value[i] == '"')
			fragment = extract_double_quoted(value, &i);
		else if (value[i] == '$')
			fragment = expand_variable(value, &i, env, last_status);
		else
			fragment = extract_plain_text(value, &i);
		result = ft_strjoin_free(result, fragment);		
	}
	return (result);
}

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
 * @brief Expands the content of the tokens in the list
 * 
 * @param list The token's list
 * @param env The environment list
 * @param last_status The last state returned by the system
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
