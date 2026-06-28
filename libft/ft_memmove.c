/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 12:29:28 by bconejo-          #+#    #+#             */
/*   Updated: 2026/06/28 01:25:57 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Copies 'len' bytes from string 'src' to string 'dst'
 * 
 * @param dst The string destiny
 * @param src The string source
 * @param len The number of bytes to copy 
 * @return Returns the original value of 'dst' 
 */
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char			*d;
	unsigned const char		*s;
	size_t					i;

	if (!dst && !src && len != 0)
		return (NULL);
	d = dst;
	s = src;
	if (d > s && d < s + len)
	{
		while (len > 0)
		{
			len--;
			d[len] = s[len];
		}
		return (d);
	}
	i = 0;
	while (i < len)
	{
		d[i] = s[i];
		i++;
	}
	return (d);
}
