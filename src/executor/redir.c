/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:32:29 by jcolina-          #+#    #+#             */
/*   Updated: 2026/09/04 18:32:30 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
* @brief Reads lines from standard input until the delimiter is found
*
* @param shell The global status of minishell
* @param limit The delimiter string to stop the heredoc
* @param fd The file descriptor of the pipe to write the input to
*/
static void	heredoc_loop(t_shell *shell, char *limit, int fd)
{
	char	*line;

	while (1)
	{
		line = readline("\033[1;34m\002> \033[0m\002");
		if (g_signal == S_SIGINT_CMD || g_signal == S_CANCEL_EXEC)
		{
			free_mem(line);
			close(fd);
			end_shell(shell);
			exit(130);
		}
		if (!line || !ft_strcmp(line, limit))
		{
			free_mem(line);
			close(fd);
			end_shell(shell);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free_mem(line);
	}
}

/**
* @brief Closes all redirections greater than 2 to prevent FD leaks in heredoc
*
* @param shell The global status of minishell
*/
static void	close_heredoc_fds(t_shell *shell)
{
	t_cmd	*tmp_cmd;
	t_redir	*tmp_redir;

	tmp_cmd = shell->cmd;
	while (tmp_cmd)
	{
		tmp_redir = tmp_cmd->redirs;
		while (tmp_redir)
		{
			if (tmp_redir->redir_in > 2)
				close(tmp_redir->redir_in);
			if (tmp_redir->redir_out > 2)
				close(tmp_redir->redir_out);
			tmp_redir = tmp_redir->next;
		}
		tmp_cmd = tmp_cmd->next;
	}
}

/**
* @brief Checks the exit status of the heredoc child process
*
* @param status The waitpid status integer
* @param fd_zero The read end of the heredoc pipe
* @return The fd to read from, or -1 if execution was cancelled by signal
*/
static int	check_heredoc_status(int status, int fd_zero)
{
	if ((WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
		|| (WIFEXITED(status) && WEXITSTATUS(status) == 130))
	{
		g_signal = S_SIGINT_CMD;
		printf("\n");
		close(fd_zero);
		return (-1);
	}
	return (fd_zero);
}

/**
* @brief Creates a pipe and forks a process to execute a heredoc
*
* @param shell The global status of minishell
* @param limit The delimiter string to stop the heredoc
* @return The read end of the pipe, or -1 if it fails
*/
int	heredoc(t_shell *shell, char *limit)
{
	pid_t	pid;
	int		fd[2];
	int		status;

	if (pipe(fd) < 0)
		return (ft_putendl_fd("failed to open pipe", 2), 1);
	pid = fork();
	if (pid < 0)
		return (ft_putendl_fd("failed to open fork", 2), 1);
	if (pid == 0)
	{
		signal(SIGINT, heredoc_sigint_handler);
		g_signal = S_HEREDOC;
		close(fd[0]);
		close_heredoc_fds(shell);
		heredoc_loop(shell, limit, fd[1]);
	}
	g_signal = S_HEREDOC_END;
	waitpid(pid, &status, 0);
	close(fd[1]);
	return (check_heredoc_status(status, fd[0]));
}
