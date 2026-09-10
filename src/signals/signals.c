/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:49:29 by jcolina-          #+#    #+#             */
/*   Updated: 2026/09/04 18:49:30 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int		g_signal;

/**
 * @brief Initializes the shell's signal handling
 *
 * This function Initializes the shell's signal handling, estalishing the
 * signal handlers for SIGINT and SIGQUIT. It also initializes the
 * g_signal variable
 */
void	signal_init(void)
{
	g_signal = S_BASE;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

/**
 * @brief Signal handler for SIGINT y SIGQUIT.
 *
 * This function handles de SIGINT and SIGQUIT signals. Depending on the actual
 * state of g_signal, it does specific actions like interrupting a command
 * exectuion, canceling an execution command, or finalizing a heredoc.
 *
 * @param sig is the recieved signal's number
 */
void	sigint_handler(int sig)
{
	(void)sig;
	if (g_signal == S_BASE || g_signal == S_SIGINT)
	{
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_signal = S_SIGINT;
	}
	else if (g_signal == S_CMD)
	{
		ft_putstr_fd("\n", 1);
		g_signal = S_SIGINT_CMD;
	}
	else if (g_signal == S_HEREDOC)
	{
		g_signal = S_SIGINT_CMD;
	}
	sigint_handler_aux();
}

/**
 * @brief Auxiliary function for the purpose of handling additional SIGINT cases.
 *
 * This function manages additional SIGINT cases not directly covered by the main
 * handler. For examplem canceling a heredoc execution or stablishing the
 * S_SIGINT signal into base state or heredoc.
 */
void	sigint_handler_aux(void)
{
	if (g_signal == S_HEREDOC_END)
	{
		ft_putstr_fd("\n", 1);
		g_signal = S_CANCEL_EXEC;
	}
	else if (g_signal == S_BASE || g_signal == S_HEREDOC)
		g_signal = S_SIGINT;
}

/**
 * @brief Signal handler for SIGINT (Ctrl+C) inside a heredoc child process
 * 
 * Updates the global signal state to indicate an interruption and safely 
 * closes the standard input (STDIN_FILENO). This forces the readline loop 
 * to break immediately, allowing the heredoc process to exit correctly.
 * 
 * @param sig The signal number (expected to be SIGINT, safely cast to void)
 */
void	heredoc_sigint_handler(int sig)
{
	(void)sig;
	g_signal = S_SIGINT_CMD;
	close(STDIN_FILENO);
}
