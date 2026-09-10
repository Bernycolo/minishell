/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:49:56 by jcolina-          #+#    #+#             */
/*   Updated: 2026/09/04 18:49:57 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Prints the environment variables list
 * 
 * @param msh The global status of minishell
 */
void	builtin_env(t_shell *msh)
{
	t_env	*tmp;

	if (msh->cmd->argc > 1)
	{
		printf("env: %s: No such file or directory\n", msh->cmd->arg[1]);
		msh->last_status = 127;
		return ;
	}
	tmp = msh->env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, "_\0"))
			printf("_=/usr/bin/env\n");
		else if (tmp->value)
			printf("%s=%s\n", tmp->key, tmp->value);
		else
			printf("%s\n", tmp->key);
		tmp = tmp->next;
	}
	msh->last_status = 0;
}
