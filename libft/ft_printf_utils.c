/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 23:43:47 by nrossa            #+#    #+#             */
/*   Updated: 2023/06/02 05:26:14 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isconversion(char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	else
		return (0);
}

int	ft_flags_length(const char *str)
{
	int	i;

	i = 0;
	while (str[i] && !ft_isconversion(str[i]))
		i++;
	return (i);
}

void	ft_check_flags(t_flags *flags)
{
	char	c;

	c = flags->conversion;
	if (flags->width < 0)
	{
		flags->width *= -1;
		flags->minus = 1;
	}
	if (flags->zero && flags->minus)
		flags->zero = 0;
	if (flags->zero && flags->dot >= 0 && (c == 'd' || c == 'i'
			|| c == 'u' || c == 'x' || c == 'X'))
		flags->zero = 0;
	if (flags->space && flags->plus)
		flags->space = 0;
	if (c == 's' && flags->zero)
		flags->zero = 0;
}
