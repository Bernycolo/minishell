/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:50:35 by jcolina-          #+#    #+#             */
/*   Updated: 2026/09/04 18:50:36 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtins_utils.h"

/**
 * @brief Gives the export attribute to the variables corresponding to
 * the specified names, which shall cause them to be in the environment of
 * subsequently executed commands. If the name of a variable is followed
 * by = word, then the value of that variable shall be set to word.
 * 
 * @param shell The global status of minishell
 */
void	builtin_export(t_shell *shell)
{
	shell->last_status = 0;
	if (shell->cmd->argc == 1)
		export_no_args(shell);
	else
		export_with_args(shell);
}
