/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 14:27:44 by bconejo-          #+#    #+#             */
/*   Updated: 2026/06/28 02:05:30 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Appends string 'src' to the end of 'dst'
 * 
 * @param dst The destiny string
 * @param src The source string
 * @param dstsize The length of the destination string
 * @return Returns the total length of the string they tried to create 
 */
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	src_len;
	size_t	dst_len;

	dst_len = 0;
	while (dst[dst_len] && dst_len < dstsize)
		dst_len++;
	src_len = 0;
	while (src[src_len])
		src_len++;
	if (dstsize == dst_len)
		return (src_len + dstsize);
	i = 0;
	while (dst_len + i < dstsize - 1 && src[i])
	{
		dst[dst_len + i] = src[i];
		i++;
	}
	dst[dst_len + i] = '\0';
	return (src_len + dst_len);
}
