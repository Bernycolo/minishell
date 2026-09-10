/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:32:16 by jcolina-          #+#    #+#             */
/*   Updated: 2026/09/04 18:32:17 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Converts the list into an array
 *
 * This function converts the enviroment list into an array chain in a 
 * "key=value" form, where each array element rpresents an enviroment variable
 * The arrays last element is NULL
 *
 * @param msh Shell pointer
 * @return Array chain that represents the enviroment variables
 * in the "key=value" format
 */
char	**env_to_array(t_shell *msh)
{
	int		len;
	t_env	*tmp;
	char	**ret;
	char	*tmp_str;

	len = 1;
	tmp = msh->env;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	ret = malloc((sizeof(char *) * len) + 1);
	tmp = msh->env;
	len = 0;
	while (tmp)
	{
		tmp_str = ft_strjoin(tmp->key, "=");
		ret[len] = ft_strjoin(tmp_str, tmp->value);
		free_mem(tmp_str);
		tmp = tmp->next;
		len++;
	}
	ret[len] = NULL;
	return (ret);
}

/**
 * @brief Iterates through commands to check and flag if they are builtins
 * 
 * @param cmd A pointer to the first command node in the list
 */
void	classify_cmd(t_cmd **cmd)
{
	t_cmd	*aux;

	aux = *cmd;
	while (aux)
	{
		if (aux->argc == 0)
			aux->is_builtin = 0;
		else
			aux->is_builtin = is_builtin(aux);
		aux = aux->next;
	}
}

/**
 * @brief Closes appropriate pipe ends in the parent process
 * 
 * @param cmd The current command node
 * @param prev_fd Pointer to the previous pipe's read end to be updated
 * @param pipefd Array containing the current pipe FDs
 */
void	close_pipe(t_cmd *cmd, int *prev_fd, int pipefd[2])
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(pipefd[1]);
		*prev_fd = pipefd[0];
	}
}

/**
 * @brief Prints a pipe error message and updates the exit status to 1
 * 
 * @param shell The global status of minishell
 * @param str The custom string to pass to perror
 */
void	exit_pipecmd(t_shell *shell, char *str)
{
	perror(str);
	shell->last_status = 1;
}
