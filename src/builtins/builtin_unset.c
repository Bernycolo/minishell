/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:50:46 by jcolina-          #+#    #+#             */
/*   Updated: 2026/09/04 18:50:47 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Unsets values of variables
 * 
 * @param shell The global status of minishell
 */
void	builtin_unset(t_shell *shell)
{
	int	i;

	i = 1;
	while (i < shell->cmd->argc)
		env_unset(&shell->env, shell->cmd->arg[i++]);
}
