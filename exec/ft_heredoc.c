/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 01:08:14 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/21 01:34:06 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	heredoc_prompt(const char *stop, int pipe_fds[2])
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			printf(PROMPT_ERROR "Received EOF when expecting `%s`\n", stop);
			break ;
		}
		if (!ft_strcmp(line, stop))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, pipe_fds[1]);
		ft_putstr_fd("\n", pipe_fds[1]);
		free(line);
	}
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	exit(0);
}

int	ft_heredoc(t_data *data, const char *stop)
{
	int	pid;
	int	status;
	int	pipe_fds[2];

	if (pipe(pipe_fds) == -1)
		return (errno);
	dup2(data->std[0], STDIN_FILENO);
	pid = fork();
	if (pid == -1)
		return (errno);
	if (pid == 0)
		heredoc_prompt(stop, pipe_fds);
	waitpid(pid, &status, 0);
	data->status_code = interpret_status(status);
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	return (data->status_code);
}
