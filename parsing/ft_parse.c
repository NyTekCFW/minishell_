/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 01:49:59 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/12 22:35:29 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_parserror(t_data *data, t_typetok type)
{
	ft_putstr_fd(PROMPT_ERROR, 2);
	ft_putstr_fd("syntax error near unexpected token `", 2);
	if (type == LESS)
		ft_putstr_fd("<", 2);
	else if (type == GREAT)
		ft_putstr_fd(">", 2);
	else if (type == DOUBLE_LESS)
		ft_putstr_fd("<<", 2);
	else if (type == DOUBLE_GREAT)
		ft_putstr_fd(">>", 2);
	else if (type == T_PIPE)
		ft_putstr_fd("|", 2);
	else if (type == NEW_LINE)
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
	data->status_code = CMD_LINE;
}

int	ft_cmd_error(t_data *data, t_token *token)
{
	t_token	*last;

	last = ft_toklst_last(token);
	if (token->type == T_PIPE)
		return (ft_parserror(data, T_PIPE), 1);
	while (token)
	{
		if (token->type == LESS || token->type == GREAT
			|| token->type == DOUBLE_LESS || token->type == DOUBLE_GREAT)
		{
			if (!token->next)
				return (ft_parserror(data, NEW_LINE), 1);
			else if (token->next && token->next->type != ARGUMENTS)
				return (ft_parserror(data, token->next->type), 1);
		}
		token = token->next;
	}
	if (last->type == T_PIPE)
		return (ft_parserror(data, T_PIPE), 1);
	return (0);
}

static void	ft_parse_tokens(t_data *data)
{
	t_token	*current;
	char	*expand_var;
	char	*strip_quotes;

	current = data->tokens;
	while (current)
	{
		if (current->value)
		{
			expand_var = ft_expand_var(data, current->value);
			free(current->value);
			strip_quotes = ft_clear_quotes(expand_var);
			free(expand_var);
			current->value = strip_quotes;
		}
		current = current->next;
	}
}

t_cmd	*ft_parse(t_data *data)
{
	t_cmd	*cmd;

	cmd = NULL;
	if (ft_cmd_error(data, data->tokens))
	{
		ft_toklst_clear(&data->tokens);
		data->tokens = NULL;
		return (NULL);
	}
	ft_parse_tokens(data);
	ft_create_cmd(&cmd, data->tokens);
	ft_toklst_clear(&data->tokens);
	data->tokens = NULL;
	return (cmd);
}
