/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putncount.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 16:56:31 by nrossa            #+#    #+#             */
/*   Updated: 2023/06/02 05:11:31 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putncount_char(char c)
{
	int	i;

	i = write(1, &c, 1);
	return (i);
}

int	ft_putncount_str(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
	return (i);
}
