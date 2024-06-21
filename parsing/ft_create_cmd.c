/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 21:52:48 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/12 22:35:36 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_arrlen(char **args)
{
	int	i;

	i = 0;
	if (!args)
		return (0);
	while (args[i])
		i++;
	return (i);
}

static char	**ft_add_args(char **args, char *str)
{
	char	**result;
	int		len;
	int		i;

	i = 0;
	len = ft_arrlen(args) + 1;
	result = malloc(sizeof(char *) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = NULL;
	if (!args)
	{
		result[i] = ft_strdup(str);
		return (result);
	}
	while (args[i])
	{
		result[i] = args[i];
		i++;
	}
	result[i] = ft_strdup(str);
	free(args);
	return (result);
}

static t_cmd_type	ft_get_cmd_type(t_token *token)
{
	if (token->type == ARGUMENTS)
		return (CMD);
	else if (token->type == LESS)
		return (INPUT);
	else if (token->type == GREAT)
		return (OUTPUT);
	else if (token->type == DOUBLE_LESS)
		return (HEREDOC);
	else if (token->type == DOUBLE_GREAT)
		return (APPEND);
	else
		return (PIPE);
}

static void	ft_add_io(t_io **lst, t_token **token)
{
	t_cmd_type	type;
	t_io		*new;
	char		*path;

	type = ft_get_cmd_type(*token);
	path = ft_strdup((*token)->next->value);
	new = ft_iolst_new(type, path);
	ft_iolst_add_back(lst, new);
	*token = (*token)->next;
}

void	ft_create_cmd(t_cmd **lst, t_token *token)
{
	t_cmd	*new;

	new = NULL;
	while (token)
	{
		if (token->type != T_PIPE)
		{
			if (!new)
				new = ft_cmdlst_new(CMD);
			if (token->type == ARGUMENTS)
				new->args = ft_add_args(new->args, token->value);
			else
				ft_add_io(&new->io, &token);
		}
		else
		{
			ft_cmdlst_add_back(lst, new);
			ft_cmdlst_add_back(lst, ft_cmdlst_new(PIPE));
			new = NULL;
		}
		token = token->next;
	}
	if (new)
		ft_cmdlst_add_back(lst, new);
}
