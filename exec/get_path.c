/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 01:08:19 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/21 01:33:06 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_absolute_path(const char *absolute_path)
{
	return (absolute_path && access(absolute_path, F_OK | X_OK) == 0);
}

static char	*search_path(const char *bin, const char **path, t_data *data)
{
	size_t	i;
	char	*temp;
	char	*absolute_path;

	i = 0;
	while (path[i])
	{
		temp = ft_strjoin(path[i++], "/");
		absolute_path = ft_strjoin(temp, bin);
		free(temp);
		if (check_absolute_path(absolute_path))
			return (absolute_path);
		free(absolute_path);
	}
	printf(PROMPT_ERROR "Command not found\n");
	data->status_code = 127;
	return (NULL);
}

char	*get_bin_path(char *bin, t_data *data)
{
	char	*path;
	char	**path_split;

	if (!bin || !data)
		return (NULL);
	if (ft_strchr(bin, '/'))
		return (ft_strdup(bin));
	path = ft_get_env_value(data, "PATH");
	if (!path)
		return (NULL);
	path_split = ft_split(path, ':');
	if (!path_split)
		return (NULL);
	path = search_path(bin, (const char **) path_split, data);
	errno = 0;
	ft_free_array(path_split);
	return (path);
}
