#include "minishell.h"

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

char	*env_get(t_env *env, char *key)
{
	t_env	*aux;

	aux = env;
	while (aux)
	{
		if (ft_strlen(key) == ft_strlen(aux->key)
				&& ft_strncmp(key, aux->key, ft_strlen(key)) == 0)
		return (aux->value);
		aux = aux->next;
	}
	return (NULL);
}

void	env_set(t_env **env, const char *key, const char *value)
{
	t_env	*aux;

	aux = *env;
	while (aux)
	{
		if (ft_strlen(key) == ft_strlen(aux->key)
				&& ft_strncmp(key, aux->key, ft_strlen(key)) == 0)
		{
			free(aux->value);
			aux->value = ft_strdup(value);
			return ;
		}
		aux = aux->next;
	}
	add_env(env, new_env(key, value));
}

void	env_unset(t_env **env, const char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (ft_strlen(key) == ft_strlen(curr->key)
				&& ft_strncmp(key, curr->key, ft_strlen(key)) == 0)
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

void	env_free(t_env **env)
{
	t_env	*aux;

	if (!env)
		return ;
	while (*env)
	{
		aux = (*env)->next;
		free((*env)->key);
		free((*env)->value);
		free(*env);
		*env = aux;
	}
}
