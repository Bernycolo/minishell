/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 19:48:38 by bconejo-          #+#    #+#             */
/*   Updated: 2026/06/25 21:05:31 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Sends the character 'c' to the specified file descriptor.
 * 
 * @param c The character to send
 * @param fd The file descriptor to write to
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
