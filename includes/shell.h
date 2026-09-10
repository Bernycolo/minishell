/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:46:51 by bconejo-          #+#    #+#             */
/*   Updated: 2026/09/04 18:46:52 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include "structs.h"

/**
 * @struct s_shell
 * @brief Global status of minishell
 *
 * Contains the environment, tokens, CMD and the exit status
 *
 */
typedef struct s_shell
{
	t_env	*env;
	t_token	*tokens;
	t_cmd	*cmd;
	char	*name;
	char	*line;
	int		last_status;
	int		running;
}			t_shell;

void				init_shell(t_shell *shell, char **envp, char **av);
void				end_shell(t_shell *shell);

#endif
