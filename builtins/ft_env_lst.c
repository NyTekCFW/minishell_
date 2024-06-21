/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_lst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 15:49:50 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/12 03:23:22 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_envlst_clear(t_env **lst)
{
	t_env	*temp;

	if (!lst)
		return ;
	while (*lst)
	{
		temp = (*lst)->next;
		ft_envlst_delone(*lst);
		*lst = temp;
	}
}

void	ft_envlst_delone(t_env *env)
{
	if (!env)
		return ;
	free(env->key);
	free(env->value);
	free(env);
	env = NULL;
}

t_env	*ft_envlst_last(t_env *env)
{
	if (!env)
		return (NULL);
	if (env->next)
		return (ft_envlst_last(env->next));
	else
		return (env);
}

void	ft_envlst_add_back(t_data *data, t_env *new)
{
	if (data && data->envlst)
		ft_envlst_last(data->envlst)->next = new;
	else
		data->envlst = new;
}

t_env	*ft_envlst_new(char *key, char *value)
{
	t_env	*new;

	if (!key)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	return (new);
}
