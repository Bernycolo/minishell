/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:32:07 by jcolina-          #+#    #+#             */
/*   Updated: 2026/09/06 12:54:02 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Iterates through all commands and closes their opened FDs
 * 
 * @param shell The global status of minishell
 */
void	close_pids(t_shell *shell)
{
	t_redir	*redir;
	t_cmd	*cmd;

	cmd = shell->cmd;
	while (cmd)
	{
		redir = cmd->redirs;
		while (redir)
		{
			if (redir->redir_in > 2)
				close(redir->redir_in);
			if (redir->redir_out > 2)
				close(redir->redir_out);
			redir = redir->next;
		}
		cmd = cmd->next;
	}
}

/**
 * @brief Waits for pipeline children and sets the global exit status
 * 
 * @param shell The global status of minishell
 * @param last_pid The PID of the last command executed in the pipeline
 */
void	exec_pipeline_cont(t_shell *shell, pid_t last_pid)
{
	int	status;

	waitpid(last_pid, &status, 0);
	if (WIFEXITED(status))
		shell->last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		shell->last_status = 128 + WTERMSIG(status);
		if (WTERMSIG(status) == SIGQUIT)
			printf("Quit (core dumped)\n");
	}
	else
		shell->last_status = 1;
	while (waitpid(-1, NULL, 0) > 0)
		continue ;
	close_pids(shell);
}

/**
 * @brief Redirects standard output to a pipe and closes the original FDs
 *
 * This function duplicates the write end of a pipe (pipefd[1]) into the 
 * standard output (STDOUT_FILENO). After the duplication, it safely closes 
 * both the read and write file descriptors of the pipe to prevent FD leaks 
 * during pipeline execution.
 *
 * @param pipefd An array of two integers representing the pipe 
 *               (pipefd[0] is the read end, pipefd[1] is the write end)
 */
void	dup_n_close_pipe(int pipefd[2])
{
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
}
