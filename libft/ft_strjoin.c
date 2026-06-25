/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 17:44:21 by bconejo-          #+#    #+#             */
/*   Updated: 2026/06/25 20:26:34 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Reserve and return a new string, formed by the concatenation
 * of 's1' and 's2'
 * 
 * @param s1 The first string
 * @param s2 The string to add to 's1'
 * @return The new string
 * 
 * NULL if memory reservation fails
 */
char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		len_s1;
	int		len_s2;
	char	*s_join;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	s_join = malloc(len_s1 + len_s2 + 1);
	if (!s_join)
		return (NULL);
	i = 0;
	while (i < len_s1 + len_s2)
	{
		if (i < len_s1)
			s_join[i] = s1[i];
		else
			s_join[i] = s2[i - len_s1];
		i++;
	}
	s_join[len_s1 + len_s2] = '\0';
	return (s_join);
}
