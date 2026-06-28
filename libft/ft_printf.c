/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 17:59:32 by bconejo-          #+#    #+#             */
/*   Updated: 2026/06/28 01:45:42 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_print(char specifier, va_list args)
{
	int	count;

	count = 0;
	if (specifier == 'c')
		count += print_char(va_arg(args, int));
	else if (specifier == 's')
		count += print_str(va_arg(args, char *));
	else if (specifier == 'p')
		count += print_ptr(va_arg(args, void *));
	else if (specifier == 'd' || specifier == 'i')
		count += print_digit(va_arg(args, int), 10, specifier);
	else if (specifier == 'u')
		count += print_udigit(va_arg(args, unsigned int), 10, specifier);
	else if (specifier == 'x' || specifier == 'X')
		count += print_digit(va_arg(args, unsigned int), 16, specifier);
	else
	{
		ft_putchar_fd(specifier, 1);
		count++;
	}
	return (count);
}

/**
 * @brief Function that mimics the original printf() function
 * 
 * @param str The string to print
 * @param ... 
 * @return Returns the number of printed characters 
 */
int	ft_printf(char const *str, ...)
{
	int		count;
	va_list	vargs;

	va_start(vargs, str);
	count = 0;
	while (*str)
	{
		if (*str == '%')
			count += my_print(*(++str), vargs);
		else
		{
			ft_putchar_fd(*str, 1);
			count++;
		}
		str++;
	}
	va_end(vargs);
	return (count);
}
