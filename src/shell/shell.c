/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:55:05 by bconejo-          #+#    #+#             */
/*   Updated: 2026/09/04 20:53:01 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/**
* @brief Updates environment variable SHLVL
*
* @param shell The global status of minishell
*/
static void	update_shellevel(t_shell *shell)
{
	char	*shlvl;
	int		new_value;

	shlvl = env_get(shell->env, "SHLVL");
	if (!shlvl)
	{
		add_env(&shell->env, new_env("SHLVL", "2"));
		return ;
	}
	else
	{
		new_value = ft_atoi(shlvl);
		free(shlvl);
		if (new_value < 0)
			new_value = 0;
		new_value++;
		shlvl = ft_itoa(new_value);
		env_set(&shell->env, "SHLVL", shlvl);
		free(shlvl);
	}
}

/**
* @brief Updates a environment variable
*
* @param env The environment list
* @param key The key to update
* @param new_value The new value to update
*/
static void	update_env_var(t_env **env, char *key, char *new_value)
{
	char	*value;

	value = env_get(*env, key);
	if (value == NULL)
		env_set(env, key, new_value);
	else
	{
		free(value);
		value = NULL;
	}
}

/**
* @brief Sets the basic environment variables
*
* @param shell The global status of minishell
*/
static void	basic_env_vars(t_shell *shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	update_env_var(&shell->env, "OLDPWD", NULL);
	update_env_var(&shell->env, "PWD", pwd);
	update_env_var(&shell->env, "MAIL", "bconejo-@student.42malaga.com");
	update_env_var(&shell->env, "_", "/usr/bin/env");
	update_env_var(&shell->env, "PS1",
		"\001\033[38;5;229m\002minishell \001\033[0m\002% \001\033[37m\002");
	update_shellevel(shell);
	free(pwd);
	return ;
}

/**
* @brief Initializes a shell struct
*
* @param shell The global status of minishell
* @param envp The system environment variables
*/
void	init_shell(t_shell *shell, char **envp, char **av)
{
	shell->env = NULL;
	shell->tokens = NULL;
	shell->cmd = NULL;
	shell->name = av[0];
	shell->line = NULL;
	shell->last_status = 0;
	shell->running = 1;
	env_init(&shell->env, envp);
	basic_env_vars(shell);
	signal_init();
}

/**
* @brief Frees the memory space occupied by environment and command list
*
* @param shell A pointer to the shell struct
*/
void	end_shell(t_shell *shell)
{
	char	*tmp;

	if (shell->line)
	{
		free(shell->line);
		shell->line = NULL;
	}
	if (!isatty(STDIN_FILENO))
	{
		while (1)
		{
			tmp = get_next_line(0);
			if (!tmp)
				break ;
			free(tmp);
		}
	}
	free_env(&shell->env);
	free_cmd(&shell->cmd);
	rl_clear_history();
}
