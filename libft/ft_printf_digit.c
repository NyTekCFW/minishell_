/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_digit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 05:48:44 by nrossa            #+#    #+#             */
/*   Updated: 2023/06/02 05:48:44 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_min_negit(void)
{
	char	*dst;

	dst = ft_itoa(2147483647);
	dst[9] += 1;
	return (dst);
}

static int	ft_dori_length(t_flags flags, char *str, int nb)
{
	int	length;

	length = ft_strlen(str);
	if (flags.dot >= 0 && flags.dot >= length)
		length += flags.dot - length;
	if (flags.dot == 0 && nb == 0)
		length = 0;
	if ((flags.plus || flags.space) && nb >= 0)
		length++;
	return (length);
}

static int	ft_print_negid(int nb, t_flags flags)
{
	char	*str;
	int		count;
	int		length;

	count = 0;
	if (nb == -2147483648)
		str = ft_min_negit();
	else
		str = ft_itoa(nb * -1);
	length = ft_dori_length(flags, str, nb) + 1;
	if (flags.plus || flags.space)
		length--;
	if (flags.width && !flags.minus && !flags.zero)
		count += ft_print_space(flags, length);
	count += ft_putncount_char('-');
	if (flags.width && flags.zero)
		count += ft_print_zero(flags, length, 'z');
	if (flags.dot >= 0)
		if (nb != 0 || flags.dot != 0)
			count += ft_print_zero(flags, ft_strlen(str), 'd');
	count += ft_putncount_str(str);
	if (flags.width && flags.minus)
		count += ft_print_space(flags, length);
	free(str);
	return (count);
}

int	ft_print_dori(va_list args, t_flags flags)
{
	char	*str;
	int		nb;
	int		count;
	int		length;

	count = 0;
	nb = va_arg(args, int);
	if (nb < 0)
		return (ft_print_negid(nb, flags));
	str = ft_itoa(nb);
	length = ft_dori_length(flags, str, nb);
	if (flags.width && !flags.minus && !flags.zero)
		count += ft_print_space(flags, length);
	count += ft_print_mors(flags, nb);
	if (flags.width && flags.zero)
		count += ft_print_zero(flags, length, 'z');
	if (flags.dot >= 0)
		if (nb != 0 || flags.dot != 0)
			count += ft_print_zero(flags, ft_strlen(str), 'd');
	if (nb != 0 || flags.dot != 0)
		count += ft_putncount_str(str);
	if (flags.width && flags.minus)
		count += ft_print_space(flags, length);
	free(str);
	return (count);
}

int	ft_print_unsigned(va_list args, t_flags flags)
{
	char			*str;
	int				count;
	int				length;
	unsigned int	nb;

	count = 0;
	nb = va_arg(args, unsigned int);
	str = ft_utoa(nb);
	length = ft_strlen(str);
	if (flags.dot >= 0 && flags.dot >= length)
		length += flags.dot - length;
	if (flags.dot == 0 && nb == 0)
		length = 0;
	count += ft_print_flags(flags, length);
	if (flags.dot >= 0)
		if (nb != 0 || flags.dot != 0)
			count += ft_print_zero(flags, ft_strlen(str), 'd');
	if (nb != 0 || flags.dot != 0)
		count += ft_putncount_str(str);
	if (flags.width && flags.minus)
		count += ft_print_space(flags, length);
	free(str);
	return (count);
}
