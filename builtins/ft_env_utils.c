/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/24 15:31:16 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/12 03:28:39 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_env_key(t_data *data, char *key)
{
	t_env	*temp;

	temp = data->envlst;
	while (temp)
	{
		if (!ft_strcmp(key, temp->key))
			return (1);
		temp = temp->next;
	}
	return (0);
}

char	*ft_get_env_value(t_data *data, char *key)
{
	t_env	*temp;

	temp = data->envlst;
	while (temp)
	{
		if (!ft_strcmp(key, temp->key))
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

void	ft_update_env(t_data *data, char *key, char *value)
{
	t_env	*temp;

	if (!data->envlst)
		ft_envlst_add_back(data, ft_envlst_new(key, value));
	if (!ft_check_env_key(data, key))
		ft_envlst_add_back(data, ft_envlst_new(key, value));
	else
	{
		temp = data->envlst;
		while (temp)
		{
			if (!ft_strcmp(key, temp->key))
			{
				if (value)
				{
					free(temp->value);
					temp->value = ft_strdup(value);
				}
				return ;
			}
			temp = temp->next;
		}
	}
}
