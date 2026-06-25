/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 18:32:10 by bconejo-          #+#    #+#             */
/*   Updated: 2026/06/25 20:22:31 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	checkin(char c, const char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

/**
 * @brief Remove all characters from the string 'set' from the beginning and
 * from the end of 's1', until find a character not belonging to 'set'. The
 * resulting string is returned with a reservation of malloc
 * 
 * @param s1 The string to be trimmed
 * @param set The characters to remove from the string
 * @return The shortened string
 * 
 * NULL if memory reservation fails
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	int		start;
	int		end;
	int		i;
	int		total;

	start = 0;
	end = 0;
	while (checkin(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (end >= start && checkin(s1[end], set))
		end--;
	total = (end - start) + 1;
	if (total < 0)
		total = 0;
	dst = malloc(total + 1);
	if (!dst)
		return (NULL);
	i = 0;
	while (i < (total))
		dst[i++] = s1[start++];
	dst[i] = '\0';
	return (dst);
}
