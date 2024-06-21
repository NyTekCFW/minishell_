/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tokenization.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 19:42:32 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/12 11:14:30 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_skip_spaces(char **str)
{
	while (**str && ft_iswhitespace(**str))
		(*str)++;
}

static t_token	*ft_get_token_lst(t_data *data, char *str)
{
	int		error;
	t_token	*token_lst;

	error = 0;
	token_lst = NULL;
	while (*str)
	{
		if (error)
			return (ft_toklst_clear(&token_lst), NULL);
		if (ft_iswhitespace(*str))
			ft_skip_spaces(&str);
		else if (ft_ismeta(str))
			error = ft_handle_meta(&str, &token_lst);
		else
			error = ft_get_args(data, &str, &token_lst);
	}
	return (token_lst);
}

t_token	*ft_tokenization(t_data *data)
{
	char	*input;
	t_token	*token_lst;

	input = data->input;
	if (ft_check_quotes(data, input))
	{
		free(input);
		data->input = NULL;
		return (NULL);
	}
	token_lst = ft_get_token_lst(data, input);
	free(input);
	data->input = NULL;
	return (token_lst);
}
