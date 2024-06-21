/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:45:28 by nrossa            #+#    #+#             */
/*   Updated: 2023/06/01 23:51:09 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_trimstart(char const *s1, char const *set)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(s1))
	{
		if (!ft_strchr(set, s1[i]))
			return (i);
		i++;
	}
	return (i);
}

static size_t	ft_trimend(char const *s1, char const *set)
{
	size_t	i;

	i = ft_strlen(s1);
	while (i)
	{
		if (!ft_strrchr(set, s1[i - 1]))
			return (i);
		i--;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*dst;
	size_t	start;
	size_t	end;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = ft_trimstart(s1, set);
	end = ft_trimend(s1, set);
	if (start >= end)
		return (ft_strdup(""));
	dst = malloc(sizeof(char) * (end - start + 1));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s1 + start, end - start + 1);
	return (dst);
}
