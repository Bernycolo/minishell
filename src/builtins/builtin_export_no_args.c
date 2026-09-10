/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_no_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:50:12 by jcolina-          #+#    #+#             */
/*   Updated: 2026/09/04 18:50:13 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Duplicates the environment list
 * 
 * @param env The environment list to duplicate
 * @return The environment list duplicated 
 */
static t_env	*env_dup(t_env *env)
{
	t_env	*new_list;
	t_env	*cur;
	t_env	*node;

	new_list = NULL;
	cur = env;
	while (cur)
	{
		if (ft_strcmp(cur->key, "_"))
		{
			node = new_env(cur->key, cur->value);
			if (!node)
			{
				free_env(&new_list);
				return (NULL);
			}
			add_env(&new_list, node);
		}
		cur = cur->next;
	}
	return (new_list);
}

/**
 * @brief Sorts a environment list
 * 
 * @param env The environment list to sort
 */
static void	env_sort(t_env *env)
{
	t_env	*i;
	t_env	*j;
	char	*tmp_key;
	char	*tmp_val;

	i = env;
	while (i && i->next)
	{
		j = i->next;
		while (j)
		{
			if (strcmp(i->key, j->key) > 0)
			{
				tmp_key = i->key;
				tmp_val = i->value;
				i->key = j->key;
				i->value = j->value;
				j->key = tmp_key;
				j->value = tmp_val;
			}
			j = j->next;
		}
		i = i->next;
	}
}

/**
 * @brief Prints a line of the environment list
 * 
 * @param key The key to print
 * @param value The value to print
 */
static void	print_export_entry(const char *key, const char *value)
{
	if (value)
		printf("declare -x %s=\"%s\"\n", key, value);
	else
		printf("declare -x %s\n", key);
}

/**
 * @brief Prints the formatted and sorted environment list
 * 
 * @param shell The global status of minishell
 */
void	export_no_args(t_shell *shell)
{
	t_env	*copy;
	t_env	*cur;

	copy = env_dup(shell->env);
	if (!copy)
	{
		shell->last_status = 1;
		return ;
	}
	env_sort(copy);
	cur = copy;
	while (cur)
	{
		print_export_entry(cur->key, cur->value);
		cur = cur->next;
	}
	free_env(&copy);
}
