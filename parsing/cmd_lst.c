/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_lst.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:22:53 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/12 19:14:35 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cmdlst_delone(t_cmd *cmd)
{
	if (!cmd)
		return ;
	ft_iolst_clear(&cmd->io);
	ft_free_array(cmd->args);
	free(cmd);
	cmd = NULL;
}

void	ft_cmdlst_clear(t_cmd **lst)
{
	t_cmd	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_cmdlst_delone(*lst);
		*lst = temp;
	}
}

t_cmd	*ft_cmdlst_last(t_cmd *cmd)
{
	if (!cmd)
		return (NULL);
	if (cmd->next)
		return (ft_cmdlst_last(cmd->next));
	else
		return (cmd);
}

void	ft_cmdlst_add_back(t_cmd **lst, t_cmd *new)
{
	if (!*lst)
		*lst = new;
	else
		ft_cmdlst_last(*lst)->next = new;
}

t_cmd	*ft_cmdlst_new(t_cmd_type type)
{
	t_cmd	*new;

	new = ft_calloc(1, sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->type = type;
	return (new);
}
