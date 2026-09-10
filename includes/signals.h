/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:47:00 by bconejo-          #+#    #+#             */
/*   Updated: 2026/09/04 18:47:01 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

extern int	g_signal;

/**
 * @enum e_signal
 * @brief Enum representing the signal types used for emulating
 * shell behaviour
*/
typedef enum e_signal
{
	S_BASE,
	S_HEREDOC,
	S_HEREDOC_END,
	S_SIGINT,
	S_SIGINT_CMD,
	S_CMD,
	S_CANCEL_EXEC,
	S_SIZE
}			t_signal;

void	signal_init(void);
void	sigint_handler(int sig);
void	sigint_handler_aux(void);
void	heredoc_sigint_handler(int sig);

#endif