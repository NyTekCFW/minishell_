/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_chara.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:52:38 by nrossa            #+#    #+#             */
/*   Updated: 2023/06/02 05:37:47 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_nstr(t_flags flags)
{
	char	*str;
	int		count;
	int		length;

	count = 0;
	length = 0;
	str = "(null)";
	if (6 > flags.dot && flags.dot >= 0)
		flags.dot = 1;
	else
		length = ft_strlen(str);
	count += ft_print_flags(flags, length);
	if (flags.dot != 1)
		count += ft_putncount_str(str);
	if (flags.width && flags.minus)
		count += ft_print_space(flags, length);
	return (count);
}

int	ft_print_str(va_list args, t_flags flags)
{
	char	*str;
	int		i;
	int		count;
	int		length;

	i = -1;
	count = 0;
	length = 0;
	str = va_arg(args, char *);
	if (!str)
		return (ft_print_nstr(flags));
	if (flags.dot >= 0)
		while (length < flags.dot && str[length])
			length++;
	else
		length = ft_strlen(str);
	count += ft_print_flags(flags, length);
	if (flags.dot >= 0)
		while (++i < length)
			count += ft_putncount_char(str[i]);
	else
		count += ft_putncount_str(str);
	if (flags.width && flags.minus)
		count += ft_print_space(flags, length);
	return (count);
}

int	ft_print_char(va_list args, t_flags flags)
{
	char	c;
	int		count;

	count = 0;
	c = va_arg(args, int);
	if (flags.width && !flags.minus)
		count += ft_print_space(flags, 1);
	count += ft_putncount_char(c);
	if (flags.width && flags.minus)
		count += ft_print_space(flags, 1);
	return (count);
}
