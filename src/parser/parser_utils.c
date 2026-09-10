/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/04 18:54:25 by bconejo-          #+#    #+#             */
/*   Updated: 2026/09/04 18:54:26 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/**
 * @brief Prints a syntax error in standar error
 *
 * @param token The token of the error
 */
void	print_syntax_error(t_token *token)
{
	if (!token || !token->next)
		ft_putendl_fd("minishell: syntax error near unexpected token `newline`",
			2);
	else if (!token->value)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		if (token->type == PIPE)
			ft_putendl_fd("|`", 2);
		else if (token->type == INPUT)
			ft_putendl_fd("<`", 2);
		else if (token->type == TRUNC)
			ft_putendl_fd(">`", 2);
		else if (token->type == APPEND)
			ft_putendl_fd(">>`", 2);
		else if (token->type == HEREDOC)
			ft_putendl_fd("<<`", 2);
	}
	else
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
		ft_putstr_fd(token->value, 2);
		if (token->next && token->next->type == PIPE)
			ft_putstr_fd(token->next->value, 2);
		ft_putendl_fd("`", 2);
	}
}
