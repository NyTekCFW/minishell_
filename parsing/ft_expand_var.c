/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_var.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 04:34:45 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/12 13:50:06 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_varcpy(t_data *data, char **dst, char **src)
{
	char	*temp;
	char	*value;
	int		len;

	(*src)++;
	len = 0;
	temp = *src;
	while (temp[len] && (temp[len] == '_' || ft_isalnum(temp[len])))
		len++;
	temp = ft_substr(*src, 0, len);
	if (!temp)
		return ;
	while (len--)
		(*src)++;
	if (ft_check_env_key(data, temp))
	{
		value = ft_get_env_value(data, temp);
		while (*value)
		{
			**dst = *value;
			(*dst)++;
			value++;
		}
	}
	free(temp);
}

static void	ft_strcpy_with_var(t_data *data, char *dst, char *src)
{
	int	in_sq;
	int	in_dq;

	in_sq = 0;
	in_dq = 0;
	while (*src)
	{
		ft_inside_quotes(*src, &in_sq, &in_dq);
		if (*src == '$' && !in_sq)
		{
			if (!ft_strncmp(src, "$?", 2))
				ft_status_cpy(data, &dst, &src);
			else
				ft_varcpy(data, &dst, &src);
		}
		if (!*src)
			break ;
		*dst = *src;
		dst++;
		src++;
	}
}

static int	ft_varlen(t_data *data, char **str)
{
	char	*temp;
	int		len;

	if (!ft_strncmp(*str, "$?", 2))
		return (ft_status_len(data, str));
	(*str)++;
	len = 0;
	temp = *str;
	while (temp[len] && (temp[len] == '_' || ft_isalnum(temp[len])))
		len++;
	temp = ft_substr(*str, 0, len);
	if (!temp)
		return (0);
	while (len--)
		(*str)++;
	if (ft_check_env_key(data, temp))
		len = ft_strlen(ft_get_env_value(data, temp));
	else
		len = 0;
	return (free(temp), len);
}

static int	ft_strlen_with_var(t_data *data, char *str)
{
	int	in_sq;
	int	in_dq;
	int	i;

	i = 0;
	in_sq = 0;
	in_dq = 0;
	while (*str)
	{
		ft_inside_quotes(*str, &in_sq, &in_dq);
		if (*str == '$' && !in_sq)
			i += ft_varlen(data, &str);
		if (!*str)
			break ;
		str++;
		i++;
	}
	return (i);
}

char	*ft_expand_var(t_data *data, char *str)
{
	char	*result;
	int		len;

	len = ft_strlen_with_var(data, str);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	ft_strcpy_with_var(data, result, str);
	return (result);
}
