/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 20:35:59 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/12 11:09:16 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H
# define SIGNAL_ERROR 128

typedef enum e_error
{
	SUCCESS,
	FAILURE,
	CMD_LINE,
	NO_PERMISSIONS = 126,
	WRONG_CMD,
	INVALID_EXIT,
	UNKNOW = 255
}	t_error;

#endif
