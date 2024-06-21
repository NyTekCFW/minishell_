/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 01:08:36 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/21 01:33:01 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_output(t_data *data, char *path)
{
	int	fd;

	(void)data;
	if (!path)
		return (1);
	fd = open(path, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
		return (errno);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	ft_input( t_data *data, char *path)
{
	int	fd;

	(void)data;
	if (!path)
		return (1);
	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (errno);
	dup2(fd, STDIN_FILENO);
	close(fd);
	return (0);
}

int	ft_append(t_data *data, char *path)
{
	int	fd;

	(void)data;
	if (!path)
		return (1);
	fd = open(path, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
		return (errno);
	dup2(fd, STDOUT_FILENO);
	close(fd);
	return (0);
}

int	redirect_streams(const t_io *io, t_data *data)
{
	int		status;
	t_io	*iterator;

	if (!io || !data)
		return (0);
	iterator = (t_io *) io;
	while (iterator)
	{
		if (iterator->type == INPUT)
			status = ft_input(data, iterator->path);
		if (iterator->type == OUTPUT)
			status = ft_output(data, iterator->path);
		if (iterator->type == APPEND)
			status = ft_append(data, iterator->path);
		if (iterator->type == HEREDOC)
			status = ft_heredoc(data, iterator->path);
		iterator = iterator->next;
		if (!status)
			continue ;
		perror(PROMPT_ERROR);
		data->status_code = status;
		return (status);
	}
	return (0);
}
