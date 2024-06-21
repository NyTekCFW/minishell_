/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:45:54 by nrossa            #+#    #+#             */
/*   Updated: 2023/06/01 23:46:08 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_length(int n)
{
	int	nb;
	int	length;

	nb = n;
	length = 2;
	if (n < 0)
	{
		nb *= -1;
		length++;
	}
	while (nb >= 10)
	{
		nb = nb / 10;
		length++;
	}
	return (length);
}

static char	*ft_min_int(void)
{
	char	*dst;

	dst = ft_itoa(-2147483647);
	dst[10] += 1;
	return (dst);
}

char	*ft_itoa(int n)
{
	int		nb;
	int		length;
	char	*dst;

	nb = n;
	if (n == -2147483648)
		return (ft_min_int());
	length = ft_find_length(n);
	dst = malloc(sizeof(char) * (length));
	if (!dst)
		return (NULL);
	dst[--length] = '\0';
	length--;
	if (n < 0)
	{
		nb *= -1;
		dst[0] = '-';
	}
	while (nb >= 10)
	{
		dst[length--] = nb % 10 + 48;
		nb = nb / 10;
	}
	dst[length] = nb + 48;
	return (dst);
}
