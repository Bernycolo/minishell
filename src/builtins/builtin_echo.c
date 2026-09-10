/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:49:52 by jcolina-          #+#    #+#             */
/*   Updated: 2026/09/04 18:49:53 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Checks the arguments of the echo command
 * 
 * @param str The argument to check
 * @return SUCCESS if it is valid, FAILURE otherwise
 */
static t_status	check_arg(char *str)
{
	int	i;

	if (!str || str[0] != '-' || str[1] != 'n')
		return (FAILURE);
	i = 1;
	while (str[i])
	{
		if (str[i] != 'n')
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

/**
 * @brief Prints a word and appends a space if not the last element
 * 
 * @param str The string to print
 * @param i A pointer to a index
 */
static void	print_word_and_space(char **str, int *i)
{
	ft_putstr_fd(str[*i], 1);
	(*i)++;
	if (str[*i])
		ft_putchar_fd(32, 1);
}

/**
 * @brief Echo the STRING(s) to standard output
 * 
 * @param msh The global status of minishell
 */
void	builtin_echo(t_shell *msh)
{
	int	i;
	int	test_arg;

	i = 1;
	test_arg = 0;
	msh->last_status = 0;
	while (msh->cmd->arg[i] && check_arg(msh->cmd->arg[i]))
	{
		test_arg = 1;
		i++;
	}
	while (msh->cmd->arg[i])
		print_word_and_space(msh->cmd->arg, &i);
	if (!test_arg)
		ft_putchar_fd('\n', 1);
}
