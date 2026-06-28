/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 13:40:54 by bconejo-          #+#    #+#             */
/*   Updated: 2026/06/28 02:13:34 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Computes the length of the string 's'
 * 
 * @param str The string to compute
 * @return The length of the string
 */
int	ft_strlen(char const *str)
{
	int	length;

	length = 0;
	while (str[length])
		length++;
	return (length);
}
