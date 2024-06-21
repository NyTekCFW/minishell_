/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_args.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 23:49:01 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/12 11:13:42 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_issep(char *str)
{
	if (ft_ismeta(str) || ft_iswhitespace(*str))
		return (1);
	else
		return (0);
}

int	ft_get_args(t_data *data, char **ptr, t_token **lst)
{
	t_token	*token;
	char	*str;
	char	*value;
	int		i;

	str = *ptr;
	i = 0;
	while (str[i] && !ft_issep(&str[i]))
	{
		if (ft_isquote(str[i]))
		{
			if (!ft_skip_quotes(str, &i))
				return (ft_quote_error(data, str[i]), 1);
		}
		else
			i++;
	}
	value = ft_substr(str, 0, i);
	if (!value)
		return (1);
	token = ft_toklst_new(value, ARGUMENTS);
	if (!token)
		return (free(value), 1);
	*ptr += i;
	return (ft_toklst_add_back(lst, token), 0);
}
