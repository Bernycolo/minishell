/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:32:36 by jcolina-          #+#    #+#             */
/*   Updated: 2026/09/04 20:39:37 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Iterates through the PATH array to find the executable
 * 
 * @param paths Array of directory paths from the PATH environment variable
 * @param cmd The command to search for
 * @return The complete path to the executable, or NULL if not found
 */
static char	*search_in_paths(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*full_path;

	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(full_path, F_OK))
			return (full_path);
		free(full_path);
	}
	return (NULL);
}

/**
 * @brief Obtains the absolute path of a command to be executed
 * 
 * @param cmd The command name or relative/absolute path
 * @param env The environment variables linked list
 * @return The dynamically allocated path to the command, or NULL
 */
char	*get_cmd_path(char *cmd, t_env *env)
{
	char	**paths;
	char	*tmp;
	char	*result;

	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, F_OK))
			return (ft_strdup(cmd));
		return (NULL);
	}
	tmp = env_get(env, "PATH");
	if (!tmp || !env)
		return (NULL);
	paths = ft_split(tmp, ':');
	free_mem(tmp);
	if (!paths)
		return (NULL);
	result = search_in_paths(paths, cmd);
	free_mem_all(paths);
	return (result);
}

/**
 * @brief Executes a system command using the execve system call.
 * 
 * Resolves the command's absolute path and converts the environment
 * variables list into an array before calling execve. If the command 
 * is empty (e.g., only redirections), it exits safely with status 0. 
 * If the command is not found or execution fails, it prints an error 
 * message to standard error and exits with status 127.
 * 
 * @param shell The global status of minishell, containing the environment.
 * @param cmd The command node containing the arguments to be executed.
 */
void	execve_cmd(t_shell *shell, t_cmd *cmd)
{
	char	*cmd_path;
	char	**envp;

	if (!cmd || !cmd->arg || !cmd->arg[0])
		exit(0);
	cmd_path = get_cmd_path(cmd->arg[0], shell->env);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->arg[0], 2);
		if (ft_strchr(cmd->arg[0], '/'))
			ft_putendl_fd(": No such file or directory", 2);
		else
			ft_putendl_fd(": command not found", 2);
		end_shell(shell);
		exit(127);
	}
	envp = env_to_array(shell);
	execve(cmd_path, cmd->arg, envp);
	perror(shell->name);
	free_mem_all(envp);
	free_mem(cmd_path);
	end_shell(shell);
	exit(127);
}

/**
 * @brief Closes all file descriptors used for a single command's redirections
 * 
 * @param redir The linked list of redirections for the command
 */
static void	close_cmd_redirs(t_redir *redir)
{
	while (redir)
	{
		if (redir->redir_in > 2)
			close(redir->redir_in);
		if (redir->redir_out > 2)
			close(redir->redir_out);
		redir = redir->next;
	}
}

/**
 * @brief Forks and executes a single non-builtin command
 * 
 * @param msh The global status of minishell
 */
void	exec_cmd(t_shell *msh)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		apply_redirs(msh->cmd);
		execve_cmd(msh, msh->cmd);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		msh->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		msh->last_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			printf("Quit (core dumped)\n");
	}
	else
		msh->last_status = 1;
	close_cmd_redirs(msh->cmd->redirs);
}
