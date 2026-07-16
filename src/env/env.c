#include "minishell.h"
#include "libft.h"

/**
 * @brief Creates a new node for the environment list
 *
 * @param key The name of the new environment variable
 * @param value The value of the new environment variable
 * @return The new node of the new environment variable
 */
t_env	*new_env(const char *key, const char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	if (env->key == NULL)
	{
		free(env);
		return (NULL);
	}
	env->value = ft_strdup(value);
	if (env->value == NULL)
	{
		free(env->key);
		free(env);
		return (NULL);
	}
	env->next = NULL;
	return (env);
}

/**
 * @brief Adds a node to the end of the environment list
 *
 * @param list The head of the environment list
 * @param new A pointer to the new node to add
 */
void	add_env(t_env **list, t_env *new)
{
	t_env	*aux;

	if (!list || !new)
		return ;
	if (*list)
	{
		aux = *list;
		while (aux->next != NULL)
			aux = aux->next;
		aux->next = new;
	}
	else if (new)
		*list = new;
}

/**
 * @brief Initializes the environment list from envp
 *
 * @param list The head of the environment list
 * @param envp The system environment variables
 */
void	env_init(t_env **list, char **envp)
{
	int		i;
	char	*equal;
	char	*key;
	char	*value;

	i = 0;
	while (envp[i])
	{
		equal = ft_strchr(envp[i], '=');
		if (equal)
		{
			key = ft_substr(envp[i], 0, equal - envp[i]);
			value = ft_strdup(equal + 1);
		}
		else
		{
			key = ft_strdup(envp[i]);
			value = ft_strdup("");
		}
		add_env(list, new_env(key, value));
		free(key);
		free(value);
		i++;
	}
}
