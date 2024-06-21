/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:01:53 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/12 03:24:54 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_extract_value(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i++;
			return (ft_substr(str, i, ft_strlen(str) - i));
		}
		i++;
	}
	return (NULL);
}

char	*ft_extract_key(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_substr(str, 0, i));
		i++;
	}
	return (ft_strdup(str));
}

void	ft_init_env(t_data *data, char **envp)
{
	int		i;
	char	*key;
	char	*value;

	if (!envp)
		return ;
	i = 0;
	while (envp[i])
	{
		key = ft_extract_key(envp[i]);
		value = ft_extract_value(envp[i]);
		ft_update_env(data, key, value);
		free(key);
		free(value);
		i++;
	}
}

int	ft_env(t_data *data)
{
	t_env	*temp;

	temp = data->envlst;
	if (!temp)
		return (1);
	while (temp)
	{
		if (temp->value)
			printf("%s=%s\n", temp->key, temp->value);
		temp = temp->next;
	}
	return (0);
}
