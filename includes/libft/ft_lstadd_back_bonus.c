/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 19:06:00 by bconejo-          #+#    #+#             */
/*   Updated: 2025/05/22 19:45:25 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
