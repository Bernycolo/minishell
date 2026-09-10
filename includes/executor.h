/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:41:59 by bconejo-          #+#    #+#             */
/*   Updated: 2026/09/04 18:42:00 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "structs.h"

void	executor(t_shell *shell);
void	exec_cmd(t_shell *msh);
char	*get_cmd_path(char *cmd, t_env *env);
char	**env_to_array(t_shell *msh);
int		fill_redirs(t_shell *shell, t_cmd *mycmd);
void	classify_cmd(t_cmd **cmd);
void	close_pipe(t_cmd *cmd, int *prev_fd, int pipefd[2]);
void	exec_pipeline_cont(t_shell *shell, pid_t last_pid);
void	dup_n_close_pipe(int pipefd[2]);
void	close_pids(t_shell *shell);
void	exit_pipecmd(t_shell *shell, char *str);
void	apply_redirs(t_cmd *cmd);
void	child_exec(t_shell *shell, t_cmd *cmd, int prev_fd, int pipefd[2]);
void	execve_cmd(t_shell *shell, t_cmd *cmd);
int		heredoc(t_shell *shell, char *limit);

#endif
