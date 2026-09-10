/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:49:47 by jcolina-          #+#    #+#             */
/*   Updated: 2026/09/04 18:49:48 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Prints the error generated when is a unknown directory
 *
 * @param shell The global status of minishell
 */
static void	exit_error_cd(t_shell *shell)
{
	char const	*msg_error;
	char		*tmp;
	char		*msg;
	char		*path;

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

/**
 * @brief Prints the error generated when the command has too many arguments
 *
 * @param shell The global status of minishell
 */
static void	error_arg(t_shell *shell)
{
	ft_putendl_fd("minishell: cd: too many arguments", 2);
	shell->last_status = 1;
}

/**
 * @brief Prints the error generated when the HOME variable is not created
 *
 * @param shell The global status of minishell
 */
static void	error_home(t_shell *shell)
{
	ft_putendl_fd("minishell: cd: HOME not set", 2);
	shell->last_status = 1;
}

/**
 * @brief Get the path object
 *
 * @param shell The global status of minishell
 * @param oldpwd The previous path
 * @return char* The new path to change
 */
static char	*get_path(t_shell *shell, char *oldpwd)
{
	char	*path;

	path = NULL;
	if (shell->cmd->argc == 1 || !ft_strcmp(shell->cmd->arg[1], "~"))
		path = env_get(shell->env, "HOME");
	else
	{
		if (ft_strcmp(shell->cmd->arg[1], "-") == 0)
		{
			path = env_get(shell->env, "OLDPWD");
			return (path);
		}
		else if (shell->cmd->arg[1][0] != '/')
			path = ft_strjoin(oldpwd, "/");
		else
			path = ft_strdup("");
		path = ft_strjoin_free(path, ft_strdup(shell->cmd->arg[1]));
	}
	return (path);
}

/**
 * @brief Changes the working directory of the current shell execution
 * environment
 *
 * @param msh The global status of minishell
 */
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
	free(path);
	free(oldpwd);
}
