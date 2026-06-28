/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:18:51 by bconejo-          #+#    #+#             */
/*   Updated: 2026/06/28 02:21:13 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Remove and free the 'lst' node and all subsequent nodes of
 * that node, using the 'del' function
 * 
 * @param lst The node list
 * @param del The function to use
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*aux;

	if (!lst || !*lst || !del)
		return ;
	aux = *lst;
	while (aux->next)
	{
		*lst = aux->next;
		del(aux->content);
		free(aux);
		aux = *lst;
	}
	del(aux->content);
	free(aux);
	*lst = NULL;
}
