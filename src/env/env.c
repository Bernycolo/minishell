#include "minishell.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	if (!env)
		return (NULL);
	env->key = ft_strdup(key);
	env->value = ft_strdup(value);
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
	int	i;
	int	j;
	t_env	*tmp;
	char	**env_var;

	i = 0;
	while (envp[i])
	{
		env_var = ft_split(envp[i], '=');
		tmp = new_env(env_var[0], env_var[1]);
		j = 0;
		while (env_var[j])
			free(env_var[j++]);
		free(env_var);
		add_env(list, tmp);
		i++;
	}
/*
	env_var = NULL;
	tmp = NULL;
	i = 0;
	env_var = ft_split(envp[i], '=');
	if (env_var)
	{
		tmp = new_env(ft_strdup(env_var[0]), ft_strdup(env_var[1]));
	}
	add_env(list, tmp);
*/
}
/*
char	*env_get(t_env *env)
{

}

t_status	env_set(t_env *env, char *key, char *value)
{

}

t_status	env_unset(t_env *env, char *key)
{

}

void	env_free(t_env env)
{

}
*/