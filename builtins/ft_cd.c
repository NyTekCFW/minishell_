/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 11:00:48 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/12 02:56:09 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_cd_error(char *str)
{
	ft_putstr_fd(PROMPT_ERROR, 2);
	ft_putstr_fd("cd: ", 2);
	perror(str);
	return (1);
}

static int	ft_change_pwd(t_data *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	ft_update_env(data, "OLDPWD", ft_get_env_value(data, "PWD"));
	ft_update_env(data, "PWD", cwd);
	return (0);
}

static int	ft_go_home(t_data *data)
{
	char	*home;

	home = ft_get_env_value(data, "HOME");
	if (!home)
	{
		ft_putstr_fd(PROMPT_ERROR, 2);
		ft_putstr_fd("cd: No HOME set in env\n", 2);
		return (1);
	}
	if (chdir(home))
		return (ft_cd_error(home));
	return (ft_change_pwd(data));
}

int	ft_cd(t_data *data, char *path)
{
	if (!path)
		return (ft_go_home(data));
	else if (chdir(path))
		return (ft_cd_error(path));
	return (ft_change_pwd(data));
}
