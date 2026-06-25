/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:19:48 by bconejo-          #+#    #+#             */
/*   Updated: 2026/06/25 20:26:41 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Reserves and returns a substring of the string 's'
 * The substring starts at index 'start' and has a maximum length of 'len'
 * 
 * @param s The string from which to create the substring
 * @param start The index of the character in 's'
 * from which to start the substring
 * @param len The maximum length of the substring
 * @return The resulting substring
 * 
 * NULL if memory reservation fails
 */
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (size <= start)
		len = 0;
	else if (len > size - start)
		len = size - start;
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
