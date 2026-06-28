/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:17:50 by bconejo-          #+#    #+#             */
/*   Updated: 2026/06/28 01:18:02 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compares byte string s1 against byte string s2. Both strings
 * are assumed to be n bytes long
 * 
 * @param s1 The string 'a'
 * @param s2 The string 'b'
 * @param n The number of bytes it compares
 * @return Returns zero if the two strings are identical, otherwise returns
 * the difference between the first two differing bytes 
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	const unsigned char	*ptr;
	const unsigned char	*ptr2;

	i = 0;
	ptr = (const unsigned char *)s1;
	ptr2 = (const unsigned char *)s2;
	while (i < n)
	{
		if (ptr[i] != ptr2[i])
			return (ptr[i] - ptr2[i]);
		i++;
	}
	return (0);
}
