/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:48:25 by nrossa            #+#    #+#             */
/*   Updated: 2023/06/02 05:18:50 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_hex_length(unsigned int nb)
{
	int	count;

	count = 0;
	if (16 <= nb)
	{
		count += ft_hex_length(nb / 16);
		count += ft_hex_length(nb % 16);
	}
	else if (nb <= 15)
		count += 1;
	return (count);
}

static int	ft_hexa_length(t_flags flags, unsigned int hexa)
{
	int	length;

	length = ft_hex_length(hexa);
	if (flags.dot >= 0 && flags.dot >= length)
		length += flags.dot - length;
	if (hexa && flags.hash)
		length += 2;
	if (flags.dot == 0 && hexa == 0)
		length = 0;
	return (length);
}

static int	ft_utohex(unsigned int nb, char c)
{
	int	count;

	count = 0;
	if (16 <= nb)
	{
		count += ft_utohex(nb / 16, c);
		count += ft_utohex(nb % 16, c);
	}
	else if (nb <= 9)
		count += ft_putncount_char(nb + 48);
	else if (10 <= nb && nb <= 15)
	{
		if (c == 'X')
			count += ft_putncount_char(nb + 55);
		else if (c == 'x')
			count += ft_putncount_char(nb + 87);
	}
	return (count);
}

int	ft_print_hexa(va_list args, t_flags flags)
{
	int				count;
	int				length;
	unsigned int	hexa;

	count = 0;
	hexa = va_arg(args, unsigned int);
	length = ft_hexa_length(flags, hexa);
	if (flags.width && !flags.minus && !flags.zero)
		count += ft_print_space(flags, length);
	count += ft_print_hash(flags, hexa);
	if (flags.width && flags.zero)
		count += ft_print_zero(flags, length, 'z');
	if (flags.dot >= 0)
		if (hexa != 0 || flags.dot != 0)
			count += ft_print_zero(flags, ft_hex_length(hexa), 'd');
	if (hexa != 0 || flags.dot != 0)
		count += ft_utohex(hexa, flags.conversion);
	if (flags.width && flags.minus)
		count += ft_print_space(flags, length);
	return (count);
}
