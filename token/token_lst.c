/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:38:29 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/12 18:24:31 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_toklst_delone(t_token *token)
{
	if (!token)
		return ;
	free(token->value);
	free(token);
	token = NULL;
}

void	ft_toklst_clear(t_token **lst)
{
	t_token	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_toklst_delone(*lst);
		*lst = temp;
	}
}

t_token	*ft_toklst_last(t_token *token)
{
	if (!token)
		return (NULL);
	if (token->next)
		return (ft_toklst_last(token->next));
	else
		return (token);
}

void	ft_toklst_add_back(t_token **lst, t_token *new)
{
	if (!*lst)
	{
		*lst = new;
		new->prev = NULL;
	}
	else
	{
		ft_toklst_last(*lst)->next = new;
		new->prev = ft_toklst_last(*lst);
	}
}

t_token	*ft_toklst_new(char *value, t_typetok type)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = value;
	new->type = type;
	return (new);
}
