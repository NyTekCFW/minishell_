/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:19:37 by nrossa            #+#    #+#             */
/*   Updated: 2023/06/02 05:10:59 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find_utoa_length(unsigned int n)
{
	int				length;
	unsigned int	nb;

	nb = n;
	length = 2;
	while (nb >= 10)
	{
		nb = nb / 10;
		length++;
	}
	return (length);
}

char	*ft_utoa(unsigned int n)
{
	char				*dst;
	int					length;
	unsigned int		nb;

	nb = n;
	length = ft_find_utoa_length(n);
	dst = malloc(sizeof(char) * (length));
	if (!dst)
		return (NULL);
	dst[--length] = '\0';
	length--;
	while (nb >= 10)
	{
		dst[length--] = nb % 10 + 48;
		nb = nb / 10;
	}
	dst[length] = nb + 48;
	return (dst);
}
