/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_meta.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 23:43:08 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/12 12:17:32 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_ismeta(char *str)
{
	if (!ft_strncmp(str, ">", 1) || !ft_strncmp(str, "<", 1)
		|| !ft_strncmp(str, "|", 1))
		return (1);
	else
		return (0);
}

static int	ft_get_meta(char **ptr, t_token **lst, t_typetok type)
{
	t_token	*token;

	token = ft_toklst_new(NULL, type);
	if (!token)
		return (1);
	ft_toklst_add_back(lst, token);
	(*ptr)++;
	if (type == DOUBLE_LESS || type == DOUBLE_GREAT)
		(*ptr)++;
	return (0);
}

int	ft_handle_meta(char **ptr, t_token **lst)
{
	if (!ft_strncmp(*ptr, "<<", 2))
		return (ft_get_meta(ptr, lst, DOUBLE_LESS));
	else if (!ft_strncmp(*ptr, ">>", 2))
		return (ft_get_meta(ptr, lst, DOUBLE_GREAT));
	else if (!ft_strncmp(*ptr, "<", 1))
		return (ft_get_meta(ptr, lst, LESS));
	else if (!ft_strncmp(*ptr, ">", 1))
		return (ft_get_meta(ptr, lst, GREAT));
	else if (!ft_strncmp(*ptr, "|", 1))
		return (ft_get_meta(ptr, lst, T_PIPE));
	else
		return (1);
}
