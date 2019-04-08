/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 21:19:52 by rmarracc          #+#    #+#             */
/*   Updated: 2019/02/21 23:52:34 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
**	display functions
*/

/*
**	TIOCGWINSZ : Recupere la taille du terminal
*/

int			display_check(t_env *env)
{
	env->col_nb = 0;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &(env->w_size));
	env->a_max = input_max_arg_len(env);
	if (env->w_size.ws_col <= 1 || env->a_max < 1)
		return (0);
	env->col_nb = env->w_size.ws_col / (env->a_max + 1);
	if (env->col_nb < 1)
		return (0);
	if (env->a_head >= env->a_nb)
		env->a_head = 0;
	if (env->a_head < 0)
		env->a_head = env->a_nb - 1;
	return (1);
}

static void	display_get_opt(t_env *env, int i, t_opt *opt)
{
	opt->selected = FALSE;
	opt->is_head = FALSE;
	opt->type = 0;
	if (i == env->a_head)
		opt->is_head = TRUE;
	if (env->a_slt[i] == 1)
		opt->selected = TRUE;
	opt->len = ft_strlen(env->a_str[i]);
	if ((opt->fd = open(env->a_str[i], O_DIRECTORY)) >= 0)
		opt->type = 1;
	else if ((opt->fd = open(env->a_str[i], O_RDONLY)) >= 0)
	{
		if ((opt->sym = open(env->a_str[i], O_RDONLY | O_NOFOLLOW)) < 0)
			opt->type = 2;
		else
		{
			opt->type = 4;
			if (opt->len >= 3 && ft_strstr(env->a_str[i], ".c")
				&& env->a_str[i][opt->len - 2] == '.')
				opt->type = 3;
			close(opt->sym);
		}
	}
	if (opt->fd >= 0)
		close(opt->fd);
}

static void	display_padding(t_env *env, int i)
{
	size_t	pad;
	size_t	j;

	pad = env->a_max + 1 - ft_strlen(env->a_str[i]);
	j = 0;
	ft_putstr_fd("\033[0m", STDIN_FILENO);
	while (j < pad)
	{
		ft_putchar_fd(' ', STDIN_FILENO);
		j++;
	}
}

static void	display_bloc(t_env *env, int i)
{
	t_opt	opt;

	display_get_opt(env, i, &opt);
	if (opt.selected == TRUE)
		tputs(tgetstr("so", NULL), 1, term_write);
	if (opt.is_head == TRUE)
		tputs(tgetstr("us", NULL), 1, term_write);
	if (opt.type == 0)
		ft_putstr_fd("\033[90m", STDIN_FILENO);
	else if (opt.type == 1)
		ft_putstr_fd("\033[94m", STDIN_FILENO);
	else if (opt.type == 2)
		ft_putstr_fd("\033[95m", STDIN_FILENO);
	else if (opt.type == 3)
		ft_putstr_fd("\033[92m", STDIN_FILENO);
	else
		ft_putstr_fd("\033[97m", STDIN_FILENO);
	ft_putstr_fd(env->a_str[i], STDIN_FILENO);
	display_padding(env, i);
	if (opt.selected == TRUE)
		tputs(tgetstr("se", NULL), 1, term_write);
	if (opt.is_head == TRUE)
		tputs(tgetstr("ue", NULL), 1, term_write);
}

void		display_args(t_env *env)
{
	int		i;

	i = 0;
	if (!(display_check(env)))
		return ;
	while (i < env->a_nb)
	{
		if (env->a_str[i])
			display_bloc(env, i);
		if (i % env->col_nb == env->col_nb - 1)
			ft_putendl_fd("", STDIN_FILENO);
		i++;
	}
}
