/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 12:33:46 by bconejo-          #+#    #+#             */
/*   Updated: 2026/06/28 01:00:32 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Tests for a decimal digit character
 * 
 * @param c The character to test
 * @return Returns the ASCII value of the character if 'true' and 0 if 'false'
 */
int	ft_isdigit(int c)
{
	if ((c > 47) && (c < 58))
		return (c);
	else
		return (0);
}
