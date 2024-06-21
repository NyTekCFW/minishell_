/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_var_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 07:41:05 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/12 13:50:12 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_inside_quotes(char c, int *in_sq, int *in_dq)
{
	if (c == SINGLE_QUOTE)
	{
		if (!*in_sq && !*in_dq)
			*in_sq = 1;
		else
			*in_sq = 0;
	}
	if (c == DOUBLE_QUOTES)
	{
		if (!*in_dq && !*in_sq)
			*in_dq = 1;
		else
			*in_dq = 0;
	}
}

void	ft_status_cpy(t_data *data, char **dst, char **src)
{
	char	*status;
	int		i;

	i = 0;
	status = ft_itoa(data->status_code);
	if (!status)
		return ;
	while (**src && !ft_iswhitespace(**src) && !ft_isquote(**src))
		(*src)++;
	while (status[i])
	{
		**dst = status[i];
		(*dst)++;
		i++;
	}
	free(status);
}

int	ft_status_len(t_data *data, char **str)
{
	char	*status;
	int		len;

	status = ft_itoa(data->status_code);
	if (!status)
		return (0);
	while (**str && !ft_iswhitespace(**str) && !ft_isquote(**str))
		(*str)++;
	len = ft_strlen(status);
	return (free(status), len);
}
