/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_flags.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 18:47:40 by nrossa            #+#    #+#             */
/*   Updated: 2023/06/02 05:19:22 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_mors(t_flags flags, int nb)
{
	int	count;

	count = 0;
	if (flags.space && nb >= 0)
		count += ft_putncount_char(' ');
	if (flags.plus && nb >= 0)
		count += ft_putncount_char('+');
	return (count);
}

int	ft_print_hash(t_flags flags, unsigned int hexa)
{
	int	count;

	count = 0;
	if (hexa && flags.hash)
	{
		if (flags.conversion == 'x')
			count += ft_putncount_str("0x");
		else if (flags.conversion == 'X')
			count += ft_putncount_str("0X");
	}
	return (count);
}

int	ft_print_space(t_flags flags, int length)
{
	int	i;

	i = 0;
	if (flags.width <= length)
		return (0);
	while (i < (flags.width - length))
		i += ft_putncount_char(' ');
	return (i);
}

int	ft_print_zero(t_flags flags, int length, char option)
{
	int	i;

	i = 0;
	if (option == 'z')
	{
		if (flags.width <= length)
			return (0);
		while (i < (flags.width - length))
			i += ft_putncount_char('0');
		return (i);
	}
	else if (option == 'd')
	{
		if (flags.dot <= length)
			return (0);
		while (i < (flags.dot - length))
			i += ft_putncount_char('0');
		return (i);
	}
	else
		return (0);
}

int	ft_print_flags(t_flags flags, int length)
{
	int	count;

	count = 0;
	if (flags.width && flags.zero)
		count += ft_print_zero(flags, length, 'z');
	else if (flags.width && !flags.minus)
		count += ft_print_space(flags, length);
	return (count);
}
