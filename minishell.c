/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 01:08:00 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/21 01:31:55 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_init_ms(t_data *data, char **envp)
{
	ft_bzero(data, sizeof(t_data));
	ft_init_env(data, envp);
	data->env = ft_lst_to_env(data);
	data->std[IN] = dup(STDIN_FILENO);
	data->std[OUT] = dup(STDOUT_FILENO);
	tcgetattr(STDIN_FILENO, &data->ms_termios);
}

static void	ft_main_exit(t_data *data)
{
	ft_clean_ms(data);
	printf("exit\n");
	exit(data->status_code);
}

static void	ft_status_exit(t_data *data, int status)
{
	ft_clean_ms(data);
	perror(PROMPT_ERROR);
	exit(status);
}

int	main(int argc, char **argv, char **envp)
{
	int		status;
	t_data	data;

	(void)argc;
	(void)argv;
	ft_init_ms(&data, envp);
	while (1)
	{
		ft_init_signals(&data);
		data.input = readline(PROMPT);
		if (!data.input)
			ft_main_exit(&data);
		if (*data.input)
			add_history(data.input);
		data.tokens = ft_tokenization(&data);
		if (!data.tokens)
			continue ;
		data.cmd = ft_parse(&data);
		status = exec_commands(data.cmd, &data);
		if (status)
			ft_status_exit(&data, status);
		if (!data.cmd)
			continue ;
	}
	return (ft_clean_ms(&data), data.status_code);
}
