/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 00:25:42 by bconejo-          #+#    #+#             */
/*   Updated: 2026/06/28 00:59:32 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @brief Converts the initial portion of the string pointed to by 'str'
 * to 'int' representation
 * 
 * @param str The string to convert
 * @return Returns the int converted
 */
int	ft_atoi(const char *str)
{
	int	i;
	int	signal;
	int	total;

	i = 0;
	signal = 1;
	total = 0;
	while (str[i] && (str[i] == ' ' || (str[i] > 8 && str[i] < 14)))
		i++;
	if (str[i] && str[i] == '-')
	{
		signal *= -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		total = (10 * total) + (str[i] - '0');
		i++;
	}
	return (total * signal);
}
