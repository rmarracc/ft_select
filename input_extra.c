/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_extra.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 21:19:52 by rmarracc          #+#    #+#             */
/*   Updated: 2019/02/05 09:10:52 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
**	input extra functions
*/

void		input_up_down(t_env *env, uint32_t end)
{
	if (env->col_nb < 1)
		return ;
	if (end == UP)
	{
		if ((env->a_head - env->col_nb) >= 0)
			env->a_head -= env->col_nb;
	}
	else if (end == DOWN)
	{
		env->a_head += env->col_nb;
		if (env->a_head >= env->a_nb)
			env->a_head %= env->col_nb;
	}
}

void		input_delete(t_env *env)
{
	int32_t		v;

	v = env->a_head;
	while (v < (env->a_nb - 1))
	{
		env->a_str[v] = env->a_str[v + 1];
		env->a_slt[v] = env->a_slt[v + 1];
		v++;
	}
	env->a_nb -= 1;
	if (env->a_nb <= 0)
		term_quit(env);
}
