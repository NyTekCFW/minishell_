/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 01:08:26 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/21 01:33:59 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// typedef struct s_cmd
// {
// 	t_cmd_type		type;
// 	char			*path;
// 	char			**args;
// 	struct s_cmd	*next;
// }	t_cmd;

t_builtin_type	get_builtin_type(t_cmd command)
{
	if (!ft_strcmp(command.args[0], "cd"))
		return (BUILTIN_CD);
	if (!ft_strcmp(command.args[0], "echo"))
		return (BUILTIN_ECHO);
	if (!ft_strcmp(command.args[0], "env"))
		return (BUILTIN_ENV);
	if (!ft_strcmp(command.args[0], "exit"))
		return (BUILTIN_EXIT);
	if (!ft_strcmp(command.args[0], "export"))
		return (BUILTIN_EXPORT);
	if (!ft_strcmp(command.args[0], "pwd"))
		return (BUILTIN_PWD);
	if (!ft_strcmp(command.args[0], "unset"))
		return (BUILTIN_UNSET);
	return (NAB);
}

int	interpret_status(int status)
{
	int	true_status;

	if (WIFEXITED(status))
	{
		true_status = WEXITSTATUS(status);
		return (true_status + 113 * (true_status == 13));
	}
	return (128 + WTERMSIG(status));
}
