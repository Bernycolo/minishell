/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconejo- <bconejo-@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 14:49:47 by bconejo-          #+#    #+#             */
/*   Updated: 2026/06/28 01:39:01 by bconejo-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_char(int c)
{
	ft_putchar_fd(c, 1);
	return (1);
}

int	print_str(char *str)
{
	if (str == NULL)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	ft_putstr_fd(str, 1);
	return (ft_strlen(str));
}

int	print_ptr(void *ptr)
{
	int		count;

	if (!ptr)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	else
	{
		ft_putstr_fd("0x", 1);
		count = 2;
		count += print_udigit((unsigned long)ptr, 16, 'x');
		return (count);
	}
}

int	print_digit(long n, int base, char specifier)
{
	int		count;
	char	*digits;

	digits = "0123456789abcdef";
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		return (print_digit(-n, base, specifier) + 1);
	}
	if (n < base)
	{
		if (specifier == 'x')
			return (print_char(digits[n]));
		else if (n > 9)
			return (print_char(digits[n] - 32));
		else
			return (print_char(digits[n]));
	}
	else
	{
		count = print_digit(n / base, base, specifier);
		return (count + print_digit(n % base, base, specifier));
	}
}

int	print_udigit(unsigned long n, int base, char specifier)
{
	int		count;
	char	*digits;

	digits = "0123456789abcdef";
	if (n < (unsigned)base)
	{
		if (specifier == 'x')
			return (print_char(digits[n]));
		else if (n > 9)
			return (print_char(digits[n] - 32));
		else
			return (print_char(digits[n]));
	}
	else
	{
		count = print_udigit(n / base, base, specifier);
		return (count + print_udigit(n % base, base, specifier));
	}
}
