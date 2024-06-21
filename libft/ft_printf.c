/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 18:19:52 by nrossa            #+#    #+#             */
/*   Updated: 2023/06/02 05:26:36 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_catch_widot(const char *str, t_flags *flags, va_list args)
{
	int	i;

	i = 0;
	if ('1' <= str[i] && str[i] <= '9')
		flags->width = ft_atoi(str);
	else if (str[i] == '*')
		flags->width = va_arg(args, int);
	else if (str[i] == '.')
	{
		i++;
		if (str[i] == '*')
			flags->dot = va_arg(args, int);
		else
		{
			if (ft_isconversion(str[i]))
				flags->dot = 0;
			else
				flags->dot = ft_atoi(&str[i]);
		}
	}
	while (('0' <= str[i] && str[i] <= '9') || str[i] == '*')
		i++;
	return (i - 1);
}

static void	ft_catch(const char *str, t_flags *flags, va_list args)
{
	int	i;

	i = 0;
	while (str[i] && !ft_isconversion(str[i]))
	{
		if (str[i] == '-')
			flags->minus = 1;
		else if (str[i] == '0')
			flags->zero = 1;
		else if (str[i] == '+')
			flags->plus = 1;
		else if (str[i] == ' ')
			flags->space = 1;
		else if (str[i] == '#')
			flags->hash = 1;
		else if (('1' <= str[i] && str[i] <= '9') || str[i] == '*')
			i += ft_catch_widot(&str[i], flags, args);
		else if (str[i] == '.')
			i += ft_catch_widot(&str[i], flags, args);
		i++;
	}
	if (ft_isconversion(str[i]))
		flags->conversion = str[i];
	ft_check_flags(flags);
}

static int	ft_dispatch(va_list args, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.conversion == '%')
		count = ft_putncount_char(flags.conversion);
	else if (flags.conversion == 'd' || flags.conversion == 'i')
		count = ft_print_dori(args, flags);
	else if (flags.conversion == 'c')
		count = ft_print_char(args, flags);
	else if (flags.conversion == 's')
		count = ft_print_str(args, flags);
	else if (flags.conversion == 'u')
		count = ft_print_unsigned(args, flags);
	else if (flags.conversion == 'x' || flags.conversion == 'X')
		count = ft_print_hexa(args, flags);
	else if (flags.conversion == 'p')
		count = ft_print_aptr(args, flags);
	return (count);
}

static int	ft_catch_and_dispatch(va_list args, const char *str)
{
	int		count;
	t_flags	flags;

	flags = (t_flags){0, 0, 0, -1, 0, 0, 0, 0};
	ft_catch(str, &flags, args);
	count = ft_dispatch(args, flags);
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] != '%')
			count += ft_putncount_char(str[i]);
		else
		{
			i++;
			count += ft_catch_and_dispatch(args, &str[i]);
			i += ft_flags_length(&str[i]);
		}
		i++;
	}
	va_end(args);
	return (count);
}
