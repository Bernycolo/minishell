/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:55:29 by bconejo-          #+#    #+#             */
/*   Updated: 2026/09/10 15:28:56 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Clears the terminal screen and prints a wellcome message
 * 
 * @param shell The global status of minishell
 */
static void	clean_screen(t_shell *shell)
{
	printf("\033[3J\033[2J\033[H");
	printf("Welcome to %s!\n", shell->name + 2);
}

/**
 * @brief Displays the prompt and reads the user input
 * 
 * Retrieves the PS1 environment variable to use as the prompt string,
 * calls readline to get the user's input and free the prompt string
 * 
 * @param shell The global status of minishell
 * @return A dinamically allocated string containing the user input,
 * 	   or NULL if EOF (Ctrl+D) is encountered
 */
static char	*get_prompt(t_shell *shell)
{
	char	*prompt;
	char	*line;

	prompt = env_get(shell->env, "PS1");
	line = readline(prompt);
	free(prompt);
	return (line);
}

/**
 * @brief Executes the minishell in interactive mode
 * 
 * Enters in the main funtion loop,displaying the prompt, parsing the input
 * and executing commands. If safely handels EOF (Ctrl+D) and command history
 * 
 * @param shell The global status of minishell
 * @return The exit status of the last executed command 
 */
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

/**
 * @brief Executes the minishell in non-interactive mode
 * 
 * Reads commands directly from standard input using get_next_line,
 * without displaying a prompt or using readline history, executing them
 * sequentially
 * 
 * @param shell The global status of minishell
 * @return The exit status of the last executed command
 */
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

/**
 * @brief The main entry point for the minishell program
 * 
 * Initializes the shell environment and determines whether to run in
 * interactive or non-interactive mode based in the standard input (isatty)
 * 
 * @param ac The argument count
 * @param av The argument vector
 * @param envp The environment variables provided by the operating system
 * @return The final exit status of the shell, or 1 if invalid arguments
 * are provided
 */
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
