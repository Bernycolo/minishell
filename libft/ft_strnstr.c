/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 21:31:45 by bconejo-          #+#    #+#             */
/*   Updated: 2025/05/15 18:13:16 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	const unsigned char	*h = (const unsigned char *)haystack;
	const unsigned char	*n = (const unsigned char *)needle;
	size_t				i;
	size_t				j;

	i = 0;
	if (!n[i])
		return ((char *)h);
	while (h[i] && i < len)
	{
		j = 0;
		while (n[j] && (i + j < len) && h[i + j] == n[j])
			j++;
		if (!n[j])
			return ((char *)&h[i]);
		i++;
	}
	return (NULL);
}
