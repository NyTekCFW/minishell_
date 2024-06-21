/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:10:11 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/12 19:13:58 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_iolst_delone(t_io *io)
{
	if (!io)
		return ;
	free(io->path);
	free(io);
	io = NULL;
}

void	ft_iolst_clear(t_io **lst)
{
	t_io	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_iolst_delone(*lst);
		*lst = temp;
	}
}

t_io	*ft_iolst_last(t_io *io)
{
	if (!io)
		return (NULL);
	if (io->next)
		return (ft_iolst_last(io->next));
	else
		return (io);
}

void	ft_iolst_add_back(t_io **lst, t_io *new)
{
	if (!*lst)
		*lst = new;
	else
		ft_iolst_last(*lst)->next = new;
}

t_io	*ft_iolst_new(t_cmd_type type, char *path)
{
	t_io	*new;

	new = ft_calloc(1, sizeof(t_io));
	if (!new)
		return (NULL);
	new->type = type;
	new->path = path;
	return (new);
}
