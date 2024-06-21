/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nrossa <nrossa@student.42perpignan.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/10 14:26:39 by nrossa            #+#    #+#             */
/*   Updated: 2024/01/12 22:36:23 by nrossa           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_typetok
{
	ARGUMENTS,
	LESS,
	GREAT,
	DOUBLE_LESS,
	DOUBLE_GREAT,
	T_PIPE,
	NEW_LINE
}	t_typetok;

typedef struct s_token
{
	t_typetok		type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

#endif
