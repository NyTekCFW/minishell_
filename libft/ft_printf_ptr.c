/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:49:55 by nrossa            #+#    #+#             */
/*   Updated: 2023/06/02 05:32:10 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_ptr_length(size_t nb)
{
	int	count;

	count = 0;
	if (16 <= nb)
	{
		count += ft_ptr_length(nb / 16);
		count += ft_ptr_length(nb % 16);
	}
	else if (nb <= 15)
		count += 1;
	return (count);
}

static int	ft_ulongtohex(size_t nb)
{
	int	count;

	count = 0;
	if (16 <= nb)
	{
		count += ft_ulongtohex(nb / 16);
		count += ft_ulongtohex(nb % 16);
	}
	else if (nb <= 9)
		count += ft_putncount_char(nb + 48);
	else if (10 <= nb && nb <= 15)
		count += ft_putncount_char(nb + 87);
	return (count);
}

static int	ft_print_nptr(t_flags flags)
{
	int		count;
	int		length;
	char	*null_ptr;

	count = 0;
	null_ptr = "(nil)";
	length = ft_strlen(null_ptr);
	if (flags.width && !flags.minus)
		count += ft_print_space(flags, length);
	count += ft_putncount_str(null_ptr);
	if (flags.width && flags.minus)
		count += ft_print_space(flags, length);
	return (count);
}

int	ft_print_aptr(va_list args, t_flags flags)
{
	int		count;
	int		length;
	void	*ptr;

	count = 0;
	ptr = va_arg(args, void *);
	if (!ptr)
		return (ft_print_nptr(flags));
	length = ft_ptr_length((size_t)ptr) + 2;
	if (flags.width && !flags.minus)
		count += ft_print_space(flags, length);
	count += ft_putncount_str("0x");
	count += ft_ulongtohex((size_t)ptr);
	if (flags.width && flags.minus)
		count += ft_print_space(flags, length);
	return (count);
}
