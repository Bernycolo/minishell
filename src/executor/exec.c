/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:31:56 by jcolina-          #+#    #+#             */
/*   Updated: 2026/09/05 14:49:21 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Prepares and opens all file descriptors for the command list
 * 
 * @param shell The global status of minishell
 * @return SUCCESS if all redirections are valid, FAILURE otherwise
 */
static t_status	prepare_redirections(t_shell *shell)
{
	t_cmd	*mycmd;
	int		tmp;
	int		ret;

	mycmd = shell->cmd;
	ret = 1;
	while (mycmd)
	{
		tmp = fill_redirs(shell, mycmd);
		if (!tmp)
			ret = 0;
		mycmd = mycmd->next;
	}
	if (ret)
		return (SUCCESS);
	else
		return (FAILURE);
}

/**
 * @brief Executes a single command when no pipes are involved
 * 
 * If the command is a builtin, it saves STDIN and STDOUT, applies redirs,
 * executes the builtin in the parent process, and restores the standard FDs.
 * If it's an external command, it forks and executes normally
 * 
 * @param shell The global status of minishell
 */
static void	execute_single(t_shell *shell)
{
	int	ant_stdin;
	int	ant_stdout;

	if (shell->cmd->is_builtin)
	{
		ant_stdin = dup(STDIN_FILENO);
		ant_stdout = dup(STDOUT_FILENO);
		apply_redirs(shell->cmd);
		exec_builtin(shell);
		dup2(ant_stdin, STDIN_FILENO);
		dup2(ant_stdout, STDOUT_FILENO);
		close(ant_stdin);
		close(ant_stdout);
		return ;
	}
	else
		exec_cmd(shell);
	return ;
}

/**
 * @brief Handles dup2 and executes the command inside a child process
 * 
 * @param shell The global status of minishell
 * @param cmd The current command node to execute
 * @param prev_fd The read end of the previous pipe (or -1 if first command)
 * @param pipefd Array containing the current pipe FDs
 */
void	child_exec(t_shell *shell, t_cmd *cmd, int prev_fd, int pipefd[2])
{
	t_cmd	*backup_cmd;

	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (cmd->next)
		dup_n_close_pipe(pipefd);
	signal(SIGQUIT, SIG_DFL);
	apply_redirs(cmd);
	if (cmd->is_builtin)
	{
		backup_cmd = shell->cmd;
		shell->cmd = cmd;
		exec_builtin(shell);
		shell->cmd = backup_cmd;
	}
	else
		execve_cmd(shell, cmd);
	end_shell(shell);
	exit(shell->last_status);
}

/**
 * @brief Sets up pipes and forks processes for a pipeline execution
 * 
 * @param shell The global status of minishell
 */
static void	execute_pipeline(t_shell *shell)
{
	int		prev_fd;
	int		pipefd[2];
	pid_t	last_pid;
	t_cmd	*cmd;

	prev_fd = -1;
	last_pid = -1;
	cmd = shell->cmd;
	while (cmd)
	{
		if (cmd->arg && cmd->arg[0])
		{
			if (cmd->next && pipe(pipefd) < 0)
				return (exit_pipecmd(shell, "lol"));
			last_pid = fork();
			if (last_pid < 0)
				return (exit_pipecmd(shell, "fork"));
			if (last_pid == 0)
				child_exec(shell, cmd, prev_fd, pipefd);
			close_pipe(cmd, &prev_fd, pipefd);
		}
		cmd = cmd->next;
	}
	exec_pipeline_cont(shell, last_pid);
}

/**
 * @brief Main entry point for command execution.
 * 
 * Classifies commands, prepares redirections, and routes the execution 
 * to either single command mode or pipeline mode
 * 
 * @param shell The global status of minishell
 */
void	executor(t_shell *shell)
{
	classify_cmd(&shell->cmd);
	if (!shell->cmd)
		return ;
	if (prepare_redirections(shell) == SUCCESS)
	{
		if (g_signal == S_SIGINT_CMD)
			return ;
		g_signal = S_CMD;
		if (!shell->cmd->next)
			execute_single(shell);
		else
			execute_pipeline(shell);
	}
	else
		close_pids(shell);
}
