/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 04:15:52 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/05 17:47:46 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;
	size_t	length;

	if (!s1 || !s2)
		return (0);
	if (ft_strlen(s1) < ft_strlen(s2))
		length = ft_strlen(s1);
	else
		length = ft_strlen(s2);
	i = 0;
	while (i < length && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
