/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:53:53 by bconejo-          #+#    #+#             */
/*   Updated: 2026/09/04 18:53:54 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

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
	free(curr->value);
	free(curr);
	return (next);
}

/**
* @brief Expands the content of token type WORD
*
* @param value The content to expand
* @param env The environment list
* @param last_status The last state returned by the system
* @return The token's content expanded
*/
static char	*expand_word(char *value, t_env *env, int last_status)
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
			fragment = extract_double_quoted(value, &i, env, last_status);
		else if (value[i] == '~')
			fragment = expand_tilde(&i, env);
		else if (value[i] == '$' && value[i + 1] == '(')
			fragment = expand_group(value, &i, env, last_status);
		else if (value[i] == '$')
			fragment = expand_variable(value, &i, env, last_status);
		else
			fragment = extract_plain_text(value, &i);
		result = ft_strjoin_free(result, fragment);
	}
	return (result);
}

/**
 * @brief Finds the end of a group of parenthesis
 * 
 * @param value The content where to search
 * @param start The position from which to start searching
 * @return The final group position
 */
static int	find_group_end(char *value, int start)
{
	int	level;
	int	i;

	level = 1;
	i = start;
	while (value[i] && level > 0)
	{
		if (value[i] == '(')
			level++;
		else if (value[i] == ')')
			level--;
		if (level > 0)
			i++;
	}
	if (!value[i])
		return (-1);
	return (i);
}

/**
 * @brief Expands the content inside parenthesis
 * 
 * @param value The content to expand
 * @param i A pointer to a index
 * @param env The environment list
 * @param last_status The last exit status returned by the shell
 * @return The value expanded
 */
char	*expand_group(char *value, int *i, t_env *env, int last_status)
{
	int		start;
	int		end;
	char	*inside;
	char	*expanded;
	char	*res;

	*i += 2;
	start = *i;
	end = find_group_end(value, start);
	if (end == -1)
		return (ft_strdup("$("));
	inside = ft_substr(value, start, end - start);
	if (!inside)
		return (NULL);
	expanded = expand_word(inside, env, last_status);
	free(inside);
	if (!expanded)
		return (NULL);
	res = ft_strjoin("$(", expanded);
	if (!res)
		return (free(expanded), NULL);
	res = ft_strjoin_free(res, ft_strdup(")"));
	free(expanded);
	*i = end + 1;
	return (res);
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
				free(curr->value);
				curr->value = word;
			}
		}
		prev = curr;
		curr = curr->next;
	}
}
