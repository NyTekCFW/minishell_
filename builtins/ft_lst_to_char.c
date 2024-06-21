/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_char.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 23:07:33 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/12 02:23:22 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free_env(t_data *data)
{
	int	i;

	if (!data->env)
		return ;
	i = 0;
	while (data->env[i])
	{
		free(data->env[i]);
		data->env[i] = NULL;
		i++;
	}
	free(data->env);
	data->env = NULL;
}

static int	ft_envlst_size(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->value)
			i++;
		lst = lst->next;
	}
	return (i);
}

char	**ft_lst_to_env(t_data	*data)
{
	t_env	*lst;
	char	**str;
	char	*temp;
	int		size;

	ft_free_env(data);
	lst = data->envlst;
	size = ft_envlst_size(lst);
	str = malloc(sizeof(char *) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = NULL;
	size = 0;
	while (lst)
	{
		if (lst->value)
		{
			temp = ft_strjoin(lst->key, "=");
			str[size] = ft_strjoin(temp, lst->value);
			free(temp);
			size++;
		}
		lst = lst->next;
	}
	return (str);
}
