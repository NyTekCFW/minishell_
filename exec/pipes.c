/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 01:08:31 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/21 01:32:52 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	exec_builtin(t_cmd cmd_node, t_builtin_type builtin_type,
	t_data *data)
{
	if (builtin_type == BUILTIN_CD)
		return (ft_cd(data, cmd_node.args[1]));
	if (builtin_type == BUILTIN_ECHO)
		return (ft_echo(cmd_node.args));
	if (builtin_type == BUILTIN_ENV)
		return (ft_env(data));
	if (builtin_type == BUILTIN_EXIT)
		ft_exit(data, cmd_node.args);
	if (builtin_type == BUILTIN_EXPORT)
		return (ft_export(data, cmd_node.args));
	if (builtin_type == BUILTIN_PWD)
		return (ft_pwd());
	if (builtin_type == BUILTIN_UNSET)
		return (ft_unset(data, cmd_node.args));
	return (0);
}

static void	exec_child(t_cmd cmd_node, bool needs_pipe, int pipe_fds[2],
	t_data *data)
{
	t_builtin_type	builtin_type;
	char			*absolute_path;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (needs_pipe)
	{
		if (!cmd_node.have_out)
			dup2(pipe_fds[1], STDOUT_FILENO);
		close(pipe_fds[0]);
		close(pipe_fds[1]);
	}
	builtin_type = get_builtin_type(cmd_node);
	if (builtin_type != NAB)
		exit(exec_builtin(cmd_node, builtin_type, data));
	absolute_path = get_bin_path(cmd_node.args[0], data);
	if (!absolute_path)
		exit(data->status_code);
	execve(absolute_path, cmd_node.args, data->env);
	printf(PROMPT_ERROR "Permission denied\n");
	exit(errno);
}

static int	ft_fork(t_cmd cmd_node, bool needs_pipe, t_data *data)
{
	int	status;
	int	pid;
	int	pipe_fds[2];

	if (needs_pipe && pipe(pipe_fds) == -1)
		return (errno);
	if (redirect_streams(cmd_node.io, data))
		return (0);
	signal(SIGINT, &ft_parent_handler);
	signal(SIGQUIT, &ft_parent_handler);
	pid = fork();
	if (pid == -1)
		return (errno);
	if (pid == 0)
		exec_child(cmd_node, needs_pipe, pipe_fds, data);
	waitpid(pid, &status, 0);
	data->status_code = interpret_status(status);
	signal(SIGINT, &ft_sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	if (!needs_pipe)
		return (0);
	dup2(pipe_fds[0], STDIN_FILENO);
	close(pipe_fds[0]);
	close(pipe_fds[1]);
	return (0);
}

static int	exec_last(t_cmd cmd_node, t_data *data)
{
	t_builtin_type	builtin_type;

	builtin_type = get_builtin_type(cmd_node);
	if (builtin_type != NAB)
	{
		if (redirect_streams(cmd_node.io, data))
			return (0);
		data->status_code = exec_builtin(cmd_node, builtin_type, data);
		return (0);
	}
	return (ft_fork(cmd_node, false, data));
}

int	exec_commands(t_cmd *cmd_list, t_data *data)
{
	int		status;
	t_cmd	*iterator;

	if (!data || !cmd_list)
		return (1);
	iterator = cmd_list;
	while (iterator && iterator->next && iterator->next->type == PIPE)
	{
		status = ft_fork(*iterator, true, data);
		if (status)
			return (status);
		iterator = iterator->next->next;
	}
	status = exec_last(*iterator, data);
	dup2(data->std[0], STDIN_FILENO);
	dup2(data->std[1], STDOUT_FILENO);
	ft_cmdlst_clear(&cmd_list);
	return (status);
}
