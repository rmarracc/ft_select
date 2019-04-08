/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 21:19:52 by rmarracc          #+#    #+#             */
/*   Updated: 2019/02/22 00:17:26 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
**	signal functions
*/

t_env		*signal_keep_env(t_env *env)
{
	static t_env	*stock = NULL;

	if (env)
		stock = env;
	return (stock);
}

/*
**	TIOCSTI : Simuler in input terminal
*/

void		signal_suspend(void)
{
	t_env			*env;
	char			flag[2];
	int				i;

	i = 0;
	env = signal_keep_env(NULL);
	env->w_term.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(env->t_fd, TCSANOW, &(env->w_term)) < 0)
		term_error(TBADFD, env);
	tputs(tgetstr("cl", NULL), 1, term_write);
	tputs(tgetstr("te", NULL), 1, term_write);
	tputs(tgetstr("ve", NULL), 1, term_write);
	flag[0] = env->w_term.c_cc[VSUSP];
	flag[1] = '\0';
	while (i < 32)
	{
		if (i != SIGKILL && i != SIGSTOP && i != SIGCONT)
			signal(i, SIG_DFL);
		i++;
	}
	ioctl(STDIN_FILENO, TIOCSTI, flag);
}

void		signal_continue(void)
{
	t_env			*env;

	env = signal_keep_env(NULL);
	env->w_term.c_lflag &= ~(ICANON | ECHO);
	env->w_term.c_cc[VMIN] = 1;
	env->w_term.c_cc[VTIME] = 0;
	if (tcsetattr(env->t_fd, TCSANOW, &(env->w_term)) < 0)
		term_error(TBADFD, env);
	tputs(tgetstr("ti", NULL), 1, term_write);
	tputs(tgetstr("vi", NULL), 1, term_write);
	tputs(tgetstr("cl", NULL), 1, term_write);
	signal_handler(1);
	display_args(env);
}

/*
**	rc : Restaure la position du curseur
**	cd : Efface l'ecran (sans repositionner le curseur)
*/

void		signal_resize(void)
{
	t_env			*env;

	env = signal_keep_env(NULL);
	tputs(tgetstr("rc", NULL), 1, term_write);
	tputs(tgetstr("cd", NULL), 1, term_write);
	tputs(tgetstr("vi", NULL), 1, term_write);
	display_args(env);
}

void		signal_quit(void)
{
	t_env			*env;

	env = signal_keep_env(NULL);
	term_quit(env);
}
