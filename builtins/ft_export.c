/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:01:12 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/12 02:57:28 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_export_error(char *str)
{
	ft_putstr_fd(PROMPT_ERROR, 2);
	ft_putstr_fd("export: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

int	ft_isvalid_key(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (0);
	i++;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static void	ft_export_lst(t_data *data)
{
	t_env	*temp;
	int		i;

	temp = data->envlst;
	while (temp)
	{
		if (temp->value && ft_strcmp(temp->key, "_"))
		{
			printf("declare -x %s=\"", temp->key);
			i = 0;
			while ((temp->value)[i])
			{
				if ((temp->value)[i] == '$' || (temp->value)[i] == '"')
					printf("\\%c", (temp->value)[i++]);
				else
					printf("%c", (temp->value)[i++]);
			}
			printf("\"\n");
		}
		else if (!temp->value && ft_strcmp(temp->key, "_"))
			printf("declare -x %s\n", temp->key);
		temp = temp->next;
	}
}

int	ft_export(t_data *data, char **args)
{
	int		i;
	int		status;

	i = 1;
	status = 0;
	if (!args[i])
	{
		ft_export_lst(data);
		return (0);
	}
	while (args[i])
	{
		if (ft_isvalid_key(args[i]))
			ft_update_env(data, ft_extract_key(args[i]),
				ft_extract_value(args[i]));
		else
			status = ft_export_error(args[i]);
		i++;
	}
	return (status);
}
