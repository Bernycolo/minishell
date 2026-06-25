/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 18:13:07 by bconejo-          #+#    #+#             */
/*   Updated: 2026/06/25 21:01:27 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Applies the function 'f' to each character of the string 's',
 * passing its index as the first argument and the character itself as 
 * the second argument.
 * 
 * Create a new string to store the results of successive applications of 'f'
 * 
 * @param s The string to iterate
 * @param f The function to apply to each character
 * @return The string created after the correct use of 'f' on each character
 * 
 * NULL if memory reservation fails
 */
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*output;
	int		i;
	int		len;

	len = ft_strlen(s);
	output = malloc(len + 1);
	if (!output)
		return (NULL);
	i = 0;
	while (i < len)
	{
		output[i] = (*f)(i, s[i]);
		i++;
	}
	output[i] = '\0';
	return (output);
}
