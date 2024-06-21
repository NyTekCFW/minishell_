/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_end_of_string.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 21:39:11 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/10 21:39:22 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_end_of_string(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
		i++;
	return (str + i - 1);
}
