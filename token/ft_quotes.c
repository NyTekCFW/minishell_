/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 23:45:17 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/12 22:38:00 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_quote_error(t_data *data, char c)
{
	ft_putstr_fd(PROMPT_ERROR, 2);
	ft_putstr_fd("unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	data->status_code = CMD_LINE;
	return (data->status_code);
}

int	ft_isquote(int c)
{
	if (c == SINGLE_QUOTE || c == DOUBLE_QUOTES)
		return (1);
	else
		return (0);
}

int	ft_skip_quotes(char *str, int *i)
{
	char	c;

	c = str[*i];
	if (ft_strchr(str + *i + 1, c))
	{
		(*i)++;
		while (str[*i] != c)
			(*i)++;
		(*i)++;
		return (1);
	}
	return (0);
}

static void	ft_advance_quotes(char **str, char c)
{
	while (**str && **str != c)
		(*str)++;
}

int	ft_check_quotes(t_data *data, char *str)
{
	while (*str)
	{
		if (*str == SINGLE_QUOTE)
		{
			str++;
			ft_advance_quotes(&str, SINGLE_QUOTE);
			if (!*str)
				return (ft_quote_error(data, '\''));
			else
				str++;
		}
		else if (*str == DOUBLE_QUOTES)
		{
			str++;
			ft_advance_quotes(&str, DOUBLE_QUOTES);
			if (!*str)
				return (ft_quote_error(data, '"'));
			else
				str++;
		}
		if (*str && *str != SINGLE_QUOTE && *str != DOUBLE_QUOTES)
			str++;
	}
	return (0);
}
