/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcolina- <jcolina-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:50:03 by jcolina-          #+#    #+#             */
/*   Updated: 2026/09/04 18:50:04 by jcolina-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

/**
 * @brief Skips leading spaces/tabs and determines the sign and limits
 * 
 * @param str The string to parse
 * @param sign Pointer to store the calculated sign (1 or -1)
 * @param limit Pointer to store the maximum allowed limit for over/underflow
 * @return The index of the first character after spaces and signs
 */
static int	skip_spaces_tabs(char *str, int *sign, unsigned long long *limit)
{
	int	i;

	i = 0;
	*sign = 1;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			*sign = -1;
		i++;
	}
	if (*sign == -1)
		*limit = (unsigned long long) LLONG_MAX + 1ULL;
	else
		*limit = (unsigned long long) LLONG_MAX;
	return (i);
}

/**
 * @brief Parses the numeric argument and sets the correct exit status
 * 
 * @param str The numeric string to evaluate
 * @param status Pointer to store the resulting exit status code
 * @return 0 on success, 2 if an overflow or non-numeric error occurs
 */
static int	set_exit_code(char *str, int *status)
{
	int					i;
	int					sign;
	unsigned long long	num;
	unsigned long long	limit;

	num = 0;
	i = skip_spaces_tabs(str, &sign, &limit);
	while (ft_isdigit(str[i]))
	{
		if (num > limit / 10 || (num == limit / 10
				&& ((unsigned long long) str[i] - '0' > limit % 10)))
			return (*status = 2, 2);
		num = num * 10 + (str[i++] - '0');
	}
	if (sign < 0 && num == (unsigned long long) LLONG_MAX + 1ULL)
		*status = 0;
	else if (sign == -1)
		*status = (int)(-(long long) num % 256);
	else
		*status = (int)(num % 256);
	if (*status < 0)
		*status += 256;
	return (0);
}

/**
* @brief Checks the arguments of the exit command
*
* @param msh The global status of minishell
* @return The error code corresponding to the number of arguments
*
* - 0 if no error
*
* - 1 if the number of arguments is greater than one
*
* - 2 if is not an numeric argument
*
* - the number passed by argument
*/
static int	check_exit_args(t_shell *msh)
{
	int	i;

	if (msh->cmd->argc == 1)
		return (0);
	i = 0;
	while (msh->cmd->arg[1][i] == ' ' || msh->cmd->arg[1][i] == '\t')
		i++;
	if (msh->cmd->arg[1][i] == '-' || msh->cmd->arg[1][i] == '+')
		i++;
	while (msh->cmd->arg[1][i])
	{
		if (!ft_isdigit(msh->cmd->arg[1][i]))
		{
			msh->last_status = 2;
			return (2);
		}
		i++;
	}
	if (msh->cmd->argc > 2)
		return (1);
	return (set_exit_code(msh->cmd->arg[1], &msh->last_status));
}

/**
* @brief Causes the shell to exit from its current execution environment
*
* @param msh The global status of minishell
*/
void	builtin_exit(t_shell *msh)
{
	char	*tmp;
	char	*msg;
	int		check_args;

	if (isatty(STDIN_FILENO) == 1)
		ft_putendl_fd("exit", 2);
	check_args = check_exit_args(msh);
	if (check_args == 1)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		msh->last_status = 1;
		return ;
	}
	else if (check_args == 2)
	{
		tmp = ft_strjoin("minishell: exit: ", msh->cmd->arg[1]);
		msg = ft_strjoin(tmp, ": numeric argument required");
		free(tmp);
		ft_putendl_fd(msg, 2);
		free(msg);
		msh->running = 0;
		return ;
	}
	msh->running = 0;
	return ;
}
