/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean_ms.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchiva <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 01:07:34 by lchiva            #+#    #+#             */
/*   Updated: 2024/06/21 01:33:26 by lchiva           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clean_ms(t_data *data)
{
	ft_free_array(data->env);
	ft_envlst_clear(&data->envlst);
	close(data->std[IN]);
	close(data->std[OUT]);
	rl_clear_history();
}
