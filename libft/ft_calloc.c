/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 13:55:55 by bconejo-          #+#    #+#             */
/*   Updated: 2026/06/28 00:59:09 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allocates enough space for count objects that are size bytes of 
 * memory each and returns a pointer to the allocated memory
 * 
 * The allocated memory is filled with bytes of value zero
 * allocated memory
 * 
 * @param count The number of objets
 * @param size The size in bytes of each of the objects 
 * @return Returns a pointer to the allocated memory
 */
void	*ft_calloc(size_t count, size_t size)
{
	char	*ptr;
	size_t	total;

	if (count == 0 || size == 0)
		return (malloc(0));
	if (SIZE_MAX / size < count)
		return (NULL);
	total = count * size;
	ptr = malloc(total);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, total);
	return ((void *)ptr);
}
