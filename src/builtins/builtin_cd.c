#include "minishell.h"
#include "libft.h"
/*
static void	ft_change_oldpwd_env(t_shell *info);
static void	ft_change_pwd_env(t_shell *msh);
static void	add_arg_to_env(char *var, t_shell *msh);
static int	check_variable(char *name, char *value, t_shell *info);
*/

static void	exit_error_cd(t_shell *shell)
{
	char const	*msg_error;
	char	*tmp;
	char	*msg;
	char	*path;

	msg_error = strerror(errno);
	path = ft_strjoin(shell->cmd->arg[1], ": ");
	tmp = ft_strjoin("minishell: cd: ", path);
	msg = ft_strjoin(tmp, msg_error);
	ft_putendl_fd(msg, 2);
	shell->last_status = 1;
	free(path);
	free(tmp);
	free(msg);
}

static void	error_arg(t_shell *shell)
{
	ft_putendl_fd("minishell: cd: too many arguments", 2);
	shell->last_status = 1;
}

static void	error_home(t_shell *shell)
{
	ft_putendl_fd("minishell: cd: HOME not set", 2);
	shell->last_status = 1;
}

static char	*get_path(t_shell *shell, char *oldpwd)
{
	char	*path;

	if (shell->cmd->argc == 1)
		path = env_get(shell->env, "HOME");
	else
	{
		if (shell->cmd->arg[1][0] != '/')
			path = ft_strjoin(oldpwd, "/");
		else
			path = ft_strdup("");
		path = ft_strjoin_free(path, ft_strdup(shell->cmd->arg[1]));
	}
	return (path);
}

void	builtin_cd(t_shell *msh)
{
	char	*path;
	char	*oldpwd;

	msh->last_status = 0;
	if (msh->cmd->argc > 2)
	{
		error_arg(msh);
		return ;
	}
	oldpwd = getcwd(NULL, 0);
	path = get_path(msh, oldpwd);
	if (!path)
		error_home(msh);
	else
	{
		if (chdir(path) == -1)
			exit_error_cd(msh);
		else
		{
			env_set(&msh->env, "OLDPWD", oldpwd);
			env_set(&msh->env, "PWD", path);
		}
	}
	free_mem(path);
	free_mem(oldpwd);
}
/*	ft_change_oldpwd_env(msh);
	if (msh->cmd->arg[1])
		path = ft_strdup(msh->cmd->arg[1]);
	else if (!path)
		path = ft_strdup(env_get(msh->env, "HOME"));
	if (chdir(path))
		perror("cd");
	else
		ft_pwd(msh);
	if (path)
		free(path);
	ft_change_pwd_env(msh);

}

static void	ft_change_oldpwd_env(t_shell *info)
{
	char	*to_send;
	char	*path;

	path = getcwd(NULL, 0);
	to_send = ft_strjoin("OLDPWD=", path);
	add_arg_to_env(to_send, info);
	if (to_send)
		free(to_send);
	if (path)
		free(path);
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
			if (tmp->value)
				free(tmp->value);
			tmp->value = ft_strdup(pwd);
		}
		tmp = tmp->next;
	}
	if (pwd)
		free(pwd);
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

*/
