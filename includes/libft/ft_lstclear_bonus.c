/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:18:51 by bconejo-          #+#    #+#             */
/*   Updated: 2025/05/22 20:53:12 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
