/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 04:33:45 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/12 13:36:55 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_strcpy_without_quotes(char *dst, char *src)
{
	char	c;

	while (*src)
	{
		if (ft_isquote(*src))
		{
			c = *src;
			src++;
			while (*src != c)
			{
				*dst = *src;
				dst++;
				src++;
			}
		}
		else
		{
			*dst = *src;
			dst++;
		}
		src++;
	}
}

static int	ft_strlen_without_quotes(char *str)
{
	char	c;
	int		i;

	i = 0;
	while (*str)
	{
		if (ft_isquote(*str))
		{
			c = *str;
			str++;
			while (*str != c)
			{
				str++;
				i++;
			}
		}
		else
			i++;
		str++;
	}
	return (i);
}

char	*ft_clear_quotes(char *str)
{
	char	*result;
	int		len;

	len = ft_strlen_without_quotes(str);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	ft_strcpy_without_quotes(result, str);
	return (result);
}
