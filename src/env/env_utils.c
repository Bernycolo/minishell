#include "minishell.h"
#include "libft.h"

/**
 * @brief Gets the value of a key from the environment list
 *
 * @param env The head of the environment list
 * @param key The key to get its value
 * @return char* The value of the key
 */
char	*env_get(t_env *env, const char *key)
{
	t_env	*aux;

	aux = env;
	while (aux)
	{
		if (ft_strlen(key) == ft_strlen(aux->key) && ft_strncmp(key, aux->key,
				ft_strlen(key)) == 0)
			return (ft_strdup(aux->value));
		aux = aux->next;
	}
	return (NULL);
}

/**
 * @brief Sets the value of a key from the environment list
 *
 * @param env The head of the environment list
 * @param key The key to set its value
 * @param value The new value of the key
 */
void	env_set(t_env **env, const char *key, const char *value)
{
	t_env	*aux;

	aux = *env;
	while (aux)
	{
		if (ft_strlen(key) == ft_strlen(aux->key) && ft_strncmp(key, aux->key,
				ft_strlen(key)) == 0)
		{
			free(aux->value);
			aux->value = ft_strdup(value);
			return ;
		}
		aux = aux->next;
	}
	add_env(env, new_env(key, value));
}

/**
 * @brief Sets the value of a key from the environment list
 *
 * @param env The head of the environment list
 * @param key The key to set its value
 */
void	env_unset(t_env **env, const char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (ft_strlen(key) == ft_strlen(curr->key) && ft_strncmp(key, curr->key,
				ft_strlen(key)) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->key);
			free(curr->value);
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

/**
 * @brief Frees the memory space occupied by environment
 *
 * @param env A pointer to the head of the environment list
 */
void	free_env(t_env **env)
{
	t_env	*cur;
	t_env	*next;

	if (!env || !*env)
		return ;
	cur = *env;
	while (cur)
	{
		next = cur->next;
		free(cur->key);
		free(cur->value);
		free(cur);
		cur = next;
	}
	*env = NULL;
}
