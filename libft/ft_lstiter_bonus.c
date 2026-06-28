/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:55:03 by bconejo-          #+#    #+#             */
/*   Updated: 2026/06/28 02:25:54 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Iterate through the list 'lst' and apply the function 'f'
 * to the content of each node
 * 
 * @param lst The node list
 * @param f The function to use
 */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*aux;

	if (!lst)
		return ;
	aux = lst;
	while (aux->next)
	{
		f(aux->content);
		aux = aux->next;
	}
	f(aux->content);
}
