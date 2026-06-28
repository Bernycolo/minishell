/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 18:51:30 by bconejo-          #+#    #+#             */
/*   Updated: 2026/06/28 01:03:45 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(int n)
{
	int	i;

	i = 1;
	if (n < 0)
		i++;
	while (n / 10)
	{
		n /= 10;
		i++;
	}
	return (i);
}

/**
 * @brief Generates a string that represents the integer value received as
 * an argument
 * 
 * @param n The Integer to be converted
 * @return Returns the string that represents the number
 * 
 * NULL if memory reservation fails 
 */
char	*ft_itoa(int n)
{
	char			*str;
	unsigned int	number;
	int				len;

	len = length(n);
	str = malloc(len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		number = (unsigned int)-n;
	}
	else
		number = (unsigned int)n;
	if (n == 0)
		str[0] = '0';
	while (number)
	{
		str[--len] = (number % 10) + '0';
		number /= 10;
	}
	return (str);
}
