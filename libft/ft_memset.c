/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 14:30:50 by bconejo-          #+#    #+#             */
/*   Updated: 2026/06/28 01:36:15 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Writes 'len' bytes of value 'c' to the string 'b'
 * 
 * @param b The string where to write
 * @param c The value to write
 * @param len The number of bytes to write 
 * @return Returns its first argument 
 */
void	*ft_memset(void *b, int c, size_t len)
{
	char	*temp;

	temp = b;
	while (len > 0)
	{
		*temp = (unsigned) c;
		temp++;
		len--;
	}
	return (b);
}
