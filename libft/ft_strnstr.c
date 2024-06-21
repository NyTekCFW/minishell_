/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 15:52:53 by nrossa            #+#    #+#             */
/*   Updated: 2023/06/01 23:50:54 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (!little[0])
		return ((char *)big);
	while (i < len && big[i])
	{
		if (big[i] == little[0])
		{
			if (ft_strncmp((big + i), little, ft_strlen(little)) == 0)
			{
				if ((i + ft_strlen(little)) > len)
					return (NULL);
				else
					return ((char *)(big + i));
			}
		}
		i++;
	}
	return (NULL);
}
