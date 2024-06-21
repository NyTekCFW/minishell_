/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 01:08:07 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/21 01:33:48 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_exit_error(char *str)
{
	if (!str)
	{
		ft_putstr_fd(PROMPT_ERROR, 2);
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (FAILURE);
	}
	else
	{
		ft_putstr_fd(PROMPT_ERROR, 2);
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		return (CMD_LINE);
	}
}

static int	ft_check_nb(char *str)
{
	while (*str && ft_iswhitespace(*str))
		str++;
	if (!*str)
		return (0);
	if (*str == '+' || *str == '-')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	ft_exit(t_data *data, char **args)
{
	int	exit_status;

	exit_status = data->status_code;
	printf("exit\n");
	if (args[1])
	{
		if (!ft_check_nb(args[1]))
			ft_exit_error(args[1]);
		else if (args[2])
			exit_status = ft_exit_error(NULL);
		else
			exit_status = (unsigned char)ft_atoi(args[1]);
	}
	ft_clean_ms(data);
	exit(exit_status);
}
