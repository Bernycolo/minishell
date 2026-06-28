/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:03:33 by bconejo-          #+#    #+#             */
/*   Updated: 2026/06/28 02:30:38 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Iterate through the list 'lst' and apply the function 'f' to the
 * contents of each node. Create a resulting list from the correct and
 * successive application of the function 'f' to each node. The function 'del'
 * is used to remove the contents of a node, if necessary
 * 
 * @param lst The node list
 * @param f The function to use
 * @param del The function to use to remove the contents of a node 
 * @return t_list* 
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del) (void *))
{
	t_list	*list;
	t_list	*aux;

	list = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		aux = ft_lstnew(f(lst->content));
		if (!aux)
		{
			ft_lstclear(&list, del);
			return (NULL);
		}
		ft_lstadd_back(&list, aux);
		lst = lst->next;
	}
	return (list);
}
