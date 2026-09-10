/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:55:29 by bconejo-          #+#    #+#             */
/*   Updated: 2026/09/04 18:59:29 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static void	clean_screen(t_shell *shell)
{
	printf("\033[3J\033[2J\033[H");
	printf("Welcome to %s!\n", shell->name + 2);
}

static char	*get_prompt(t_shell *shell)
{
	char	*prompt;
	char	*line;

	prompt = env_get(shell->env, "PS1");
	line = readline(prompt);
	free(prompt);
	return (line);
}

int	inter_mini(t_shell shell)
{
	clean_screen(&shell);
	while (shell.running)
	{
		shell.line = get_prompt(&shell);
		if (!shell.line)
		{
			ft_putendl_fd("exit", 2);
			break ;
		}
		if (parse(shell.line, &shell))
		{
			if (g_signal != S_SIGINT_CMD)
				executor(&shell);
			free_cmd(&shell.cmd);
			g_signal = S_BASE;
		}
		if (shell.line[0])
			add_history(shell.line);
		free(shell.line);
		shell.line = NULL;
	}
	end_shell(&shell);
	return (shell.last_status);
}

int	non_intermini(t_shell shell)
{
	shell.line = read_line();
	while (shell.line && shell.running)
	{
		if (parse(shell.line, &shell))
		{
			if (g_signal != S_SIGINT_CMD)
				executor(&shell);
			free_cmd(&shell.cmd);
			g_signal = S_BASE;
			if (!shell.running)
			{
				free(shell.line);
				shell.line = NULL;
				break ;
			}
		}
		free(shell.line);
		if (shell.running)
			shell.line = read_line();
	}
	end_shell(&shell);
	return (shell.last_status);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	shell;

	if (ac > 1)
		return (1);
	init_shell(&shell, envp, av);
	if (isatty(STDIN_FILENO) == 0)
		return (non_intermini(shell));
	else
		return (inter_mini(shell));
}
