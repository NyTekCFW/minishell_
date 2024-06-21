/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:44:55 by nrossa            #+#    #+#             */
/*   Updated: 2023/06/01 23:46:04 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dst;
	size_t	total;

	total = nmemb * size;
	if (!nmemb || !size)
	{
		dst = malloc(0);
		return (dst);
	}
	if (total / nmemb != size || total / size != nmemb)
		return (NULL);
	dst = malloc(total);
	if (!dst)
		return (NULL);
	ft_bzero(dst, total);
	return ((void *)dst);
}
