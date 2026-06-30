/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:51:14 by bconejo-          #+#    #+#             */
/*   Updated: 2026/06/30 12:50:19 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Test for any character whether it is a letter or a number
 * 
 * @param c The character to test
 * @return Returns zero if the character tests 'false' and returns the value
 * ASCII if the character tests 'true'
 */
int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')
		|| (c >= 'a' && c <= 'z'))
		return (c);
	return (0);
}
