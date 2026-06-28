/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:06:00 by bconejo-          #+#    #+#             */
/*   Updated: 2026/06/28 01:05:28 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Adds a new node to the end of the list
 * 
 * @param lst A pointer to the head of a list
 * @param new A pointer to the node to add
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*output;

	if (!lst)
		return ;
	if (*lst)
	{
		output = ft_lstlast(*lst);
		output->next = new;
	}
	else if (new)
		*lst = new;
}
