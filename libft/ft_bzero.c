/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 16:16:10 by bconejo-          #+#    #+#             */
/*   Updated: 2026/06/28 00:23:44 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Writes 'n' zeroed bytes to the string 's'.
 *  If 'n' is zero, bzero() does nothing
 * 
 * @param s The string to fill
 * @param n The zero's number to fill
 */
void	ft_bzero(void *s, size_t n)
{
	char	*temp;

	temp = s;
	while (n > 0)
	{
		*temp = '\0';
		temp++;
		n--;
	}
}
