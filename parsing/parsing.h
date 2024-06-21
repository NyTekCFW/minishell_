/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 01:08:40 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/21 01:32:35 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../minishell.h"

typedef enum e_cmd_type
{
	CMD,
	INPUT,
	OUTPUT,
	HEREDOC,
	APPEND,
	PIPE
}	t_cmd_type;

typedef enum e_builtin_type
{
	NAB,
	BUILTIN_CD,
	BUILTIN_ECHO,
	BUILTIN_ENV,
	BUILTIN_EXIT,
	BUILTIN_EXPORT,
	BUILTIN_PWD,
	BUILTIN_UNSET
}	t_builtin_type;

typedef struct s_io
{
	t_cmd_type	type;
	char		*path;
	struct s_io	*next;
}	t_io;

typedef struct s_cmd
{
	t_cmd_type		type;
	char			**args;
	bool			have_out;
	t_io			*io;
	struct s_cmd	*next;
}	t_cmd;

#endif
