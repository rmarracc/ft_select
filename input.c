/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 21:19:52 by rmarracc          #+#    #+#             */
/*   Updated: 2019/02/21 23:35:57 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
**	input functions
*/

size_t		input_max_arg_len(t_env *env)
{
	int32_t		i;
	size_t		ret;
	size_t		tmp;

	ret = 0;
	i = 0;
	while (i < env->a_nb)
	{
		tmp = ft_strlen(env->a_str[i]);
		if (tmp > ret)
			ret = tmp;
		i++;
	}
	return (ret);
}

static void	input_select(t_env *env)
{
	if (env->a_slt[env->a_head] == 0)
		env->a_slt[env->a_head] = 1;
	else
		env->a_slt[env->a_head] = 0;
	env->a_head += 1;
}

static void	input_send(t_env *env)
{
	int32_t		i;

	i = 0;
	while (i < env->a_nb)
	{
		if (env->a_slt[i] == 1)
			ft_printf("%s ", env->a_str[i]);
		i++;
	}
	term_quit(env);
}

static void	input_wrapper(t_env *env, char *buf)
{
	uint32_t	end;

	end = *(uint32_t*)buf;
	if (end == LEFT)
		env->a_head -= 1;
	if (end == RIGHT)
		env->a_head += 1;
	if (end == SPACE)
		input_select(env);
	if (end == ENTER)
		input_send(env);
	if (end == ECHAP)
		term_quit(env);
	if (end == BACKSPACE || end == DELETE)
		input_delete(env);
	if (end == UP || end == DOWN)
		input_up_down(env, end);
	if (env->a_head < 0)
		env->a_head = env->a_nb - 1;
	if (env->a_head >= env->a_nb)
		env->a_head = 0;
}

void		input_wait(t_env *env)
{
	char		buf[5];

	display_args(env);
	ft_bzero(&(buf[0]), 5);
	while (read(0, buf, 4) >= 0)
	{
		input_wrapper(env, &(buf[0]));
		tputs(tgetstr("rc", NULL), 1, term_write);
		tputs(tgetstr("cd", NULL), 1, term_write);
		display_args(env);
		ft_bzero(&(buf[0]), 5);
	}
}
