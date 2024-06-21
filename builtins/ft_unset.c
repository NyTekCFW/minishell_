/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:01:44 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/12 02:23:29 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_unset_error(char *str)
{
	ft_putstr_fd(PROMPT_ERROR, 2);
	ft_putstr_fd("unset: `", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static void	ft_unset_env(t_data *data, char *key)
{
	t_env	*prev;
	t_env	*curr;

	curr = NULL;
	curr = data->envlst;
	while (curr)
	{
		if (!ft_strcmp(key, curr->key))
		{
			if (prev)
				prev->next = curr->next;
			else
				data->envlst = curr->next;
			ft_envlst_delone(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	ft_unset(t_data *data, char **args)
{
	int		i;
	int		status;

	i = 1;
	status = 0;
	if (!args[i])
		return (status);
	while (args[i])
	{
		if (ft_isvalid_key(args[i]))
			ft_unset_env(data, args[i]);
		else
			status = ft_unset_error(args[i]);
		i++;
	}
	return (status);
}
