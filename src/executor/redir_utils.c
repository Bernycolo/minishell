/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:32:22 by jcolina-          #+#    #+#             */
/*   Updated: 2026/09/04 18:32:23 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
* @brief Opens a file for input redirection and validates its existence
*
* @param tmp The redirection node containing the target file
* @return 1 on success, 0 if the file cannot be opened
*/

static int	input_asignment(t_redir *tmp)
{
	int	fd;

	fd = open(tmp->target, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("minishell: no such file or directory: ", 2);
		ft_putendl_fd(tmp->target, 2);
		return (0);
	}
	tmp->redir_in = fd;
	return (1);
}

/**
* @brief Opens the appropriate file descriptors based on the redirection type
*
* @param shell The global status of minishell
* @param tmp The current redirection node to process
* @return 1 on success, 0 on failure
*/

static int	redirect(t_shell *shell, t_redir *tmp)
{
	int	fd;

	if (tmp->type == INPUT)
	{
		return (input_asignment(tmp));
	}
	else if (tmp->type == TRUNC)
	{
		fd = open(tmp->target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		tmp->redir_out = fd;
	}
	else if (tmp->type == APPEND)
	{
		fd = open(tmp->target, O_WRONLY | O_CREAT | O_APPEND, 0644);
		tmp->redir_out = fd;
	}
	else if (tmp->type == HEREDOC)
	{
		fd = heredoc(shell, tmp->target);
		tmp->redir_in = fd;
	}
	return (1);
}

/**
* @brief Iterates and applies all redirections for a specific command
*
* @param shell The global status of minishell
* @param mycmd The command node containing the redirections list
* @return 1 if all redirections were successful, 0 otherwise
*/

int	fill_redirs(t_shell *shell, t_cmd *mycmd)
{
	t_redir	*myred;
	int		tmp;
	int		ret;

	ret = 1;
	myred = mycmd->redirs;
	while (myred)
	{
		if (g_signal == S_SIGINT_CMD)
			break ;
		tmp = redirect(shell, myred);
		if (!tmp)
			ret = 0;
		myred = myred->next;
	}
	return (ret);
}

/**
* @brief Duplicates the parsed file descriptors to STDIN and STDOUT
*
* @param cmd The command node containing the valid file descriptors
*/

void	apply_redirs(t_cmd *cmd)
{
	t_redir	*redir;

	redir = cmd->redirs;
	while (redir)
	{
		if (redir->redir_in != -1 && redir->redir_in != STDIN_FILENO)
		{
			dup2(redir->redir_in, STDIN_FILENO);
			close(redir->redir_in);
		}
		if (redir->redir_out != -1 && redir->redir_out != STDOUT_FILENO)
		{
			dup2(redir->redir_out, STDOUT_FILENO);
			close(redir->redir_out);
		}
		redir = redir->next;
	}
}
