#include "minishell.h"
#include "libft.h"

static void	ft_change_oldpwd_env(t_shell *info);
static void	ft_change_pwd_env(t_shell *msh);
static void	add_arg_to_env(char *var, t_shell *msh);
static int	check_variable(char *name, char *value, t_shell *info);

void	ft_cd(t_shell *msh)
{
	char	*path;

	path = NULL;
	if (msh->cmd->argc > 2)
		return (printf("cd :too many arguments\n"), (void) NULL);
	ft_change_oldpwd_env(msh);
	if (msh->cmd->arg[1])
		path = ft_strdup(msh->cmd->arg[1]);
	else if (!path)
		path = ft_strdup(getenv("HOME"));
	if (chdir(path))
		perror("cd");
	else
		ft_pwd(msh);
	ft_memfree(path);
	ft_change_pwd_env(msh);
}

static void	ft_change_oldpwd_env(t_shell *info)
{
	char	*to_send;
	char	*path;

	path = getcwd(NULL, 0);
	to_send = ft_strjoin("OLDPWD=", path);
	add_arg_to_env(to_send, info);
	ft_memfree(to_send);
	ft_memfree(path);
}

static void	ft_change_pwd_env(t_shell *msh)
{
	t_env	*tmp;
	char	*pwd;

	tmp = msh->env;
	while (tmp)
	{
		if (strcmp(tmp->key, "PWD") == 0) // < atención función no permitida
		{
			pwd = getcwd(NULL, 0);
			ft_memfree(tmp->value);
			tmp->value = ft_strdup(pwd);
		}
		tmp = tmp->next;
	}
	ft_memfree(pwd);
}

static void	add_arg_to_env(char *var, t_shell *msh)
{
	t_env	*env;
	char	*name;
	char	*value;

	if (!ft_strrchr(var, '='))
		return ;
	name = get_env_name(var);
	value = get_env_value(var);
	if (!check_variable(name, value, msh))
	{
		env = ft_lstnew_env(name, value, 0);
		ft_lstadd_back_env(&msh->env, env);
	}
}

static int	check_variable(char *name, char *value, t_shell *info)
{
	t_env	*ptr;

	ptr = info->env;
	if (!ptr)
		return (0);
	while (ptr)
	{
		if (!ft_strcmp(ptr->key, name))
		{
			ft_memfree(ptr->key);
			ft_memfree(ptr->value);
			ptr->key = name;
			ptr->value = value;
			return (1);
		}
		ptr = ptr->next;
	}
	return (0);
}
