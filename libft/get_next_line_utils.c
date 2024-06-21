/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 18:19:09 by nrossa            #+#    #+#             */
/*   Updated: 2023/06/02 03:51:25 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_gnldup(const char *s, ssize_t nb)
{
	char	*dst;
	int		i;

	i = 0;
	dst = malloc(sizeof(char) * (nb + 1));
	if (!dst)
		return (NULL);
	while (s[i] && i < nb)
	{
		dst[i] = s[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_gnljoin(char *s1, char *s2, ssize_t nb)
{
	char	*dst;
	ssize_t	i;
	ssize_t	c;

	if (!s2)
		return (NULL);
	s2[nb] = '\0';
	if (!s1)
		return (ft_gnldup(s2, nb));
	dst = malloc(sizeof(char) * (ft_strlen(s1) + nb + 1));
	if (!dst)
		return (NULL);
	i = 0;
	c = 0;
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	while (c < nb)
		dst[i++] = s2[c++];
	dst[i] = '\0';
	if (s1)
		free(s1);
	return (dst);
}
