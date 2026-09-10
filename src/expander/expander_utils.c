/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:54:05 by bconejo-          #+#    #+#             */
/*   Updated: 2026/09/04 18:54:06 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Extracts the text between single quotes
 * 
 * @param value The text with single quotes
 * @param i A pointer to an index
 * @return The extracted text
 */
char	*extract_single_quoted(char *value, int *i)
{
	char	*result;
	int		start;

	result = NULL;
	(*i)++;
	start = *i;
	while (value[*i] && value[*i] != '\'')
		(*i)++;
	result = ft_substr(value, start, *i - start);
	if (value[*i] == '\'')
		(*i)++;
	return (result);
}

/**
 * @brief Extracts the text between double quotes
 * 
 * @param value The text with double quotes
 * @param i A pointer to an index
 * @return The extracted text
 */
char	*extract_double_quoted(char *value, int *i, t_env *env,
			int last_status)
{
	char	*result;
	char	*fragment;
	int		start;

	(*i)++;
	result = ft_strdup("");
	while (value[*i] && value[*i] != '"')
	{
		if (value[*i] == '$')
			fragment = expand_variable(value, i, env, last_status);
		else
		{
			start = *i;
			while (value[*i] && value[*i] != '"'
				&& value[*i] != '$')
				(*i)++;
			fragment = ft_substr(value, start, *i - start);
		}
		result = ft_strjoin_free(result, fragment);
	}
	if (value[*i] == '"')
		(*i)++;
	return (result);
}

/**
 * @brief Expand the value of ~
 * 
 * @param i A pointer to a index
 * @param env The environment list
 * @return The value of HOME
 */
char	*expand_tilde(int *i, t_env *env)
{
	char	*home;

	home = env_get(env, "HOME");
	if (!home)
		home = ft_strdup("");
	(*i)++;
	return (home);
}

/**
 * @brief Expands the value of a environment variable
 * 
 * @param value The key of the variable
 * @param i A pointer to an index
 * @param env The environment list
 * @param last_status The last state returned by the system
 * @return The expanded text 
 */
char	*expand_variable(char *value, int *i, t_env *env, int last_status)
{
	char	*result;
	char	*name;
	int		start;

	(*i)++;
	if (value[*i] == '?')
		result = ft_itoa(last_status);
	else if (value[*i] == '0')
		result = ft_strdup("minishell");
	else if (value[*i] == '_' || ft_isalpha(value[*i]))
	{
		start = *i;
		while (ft_isalnum(value[*i]) || value[*i] == '_')
			(*i)++;
		name = ft_substr(value, start, *i - start);
		result = env_get(env, name);
		free(name);
		return (result);
	}
	else
		return (ft_strdup("$"));
	(*i)++;
	return (result);
}

/**
 * @brief Extracts the plain text until find quotation marks or $
 * 
 * @param value The source text
 * @param i A pointer to an index
 * @return The extracted text
 */
char	*extract_plain_text(char *value, int *i)
{
	char	*result;
	int		start;

	start = *i;
	while (value[*i] && value[*i] != '\'' && value[*i] != '"'
		&& value[*i] != '$')
		(*i)++;
	result = ft_substr(value, start, *i - start);
	return (result);
}
