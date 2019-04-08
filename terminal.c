/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 21:19:52 by rmarracc          #+#    #+#             */
/*   Updated: 2019/02/21 23:40:35 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
**	terminal functions
*/

int			term_write(int t)
{
	return (write(STDERR_FILENO, &t, 1));
}

void		term_error(t_error error, t_env *env)
{
	ft_putstr_fd("ERROR ! (ID = ", STDERR_FILENO);
	ft_putnbr_fd(error, STDERR_FILENO);
	ft_putstr_fd("), Exiting terminal\n", STDERR_FILENO);
	ft_memdel((void**)&(env->a_slt));
	exit(error);
}

void		term_quit(t_env *env)
{
	if (tcgetattr(env->t_fd, &(env->w_term)) < 0)
		term_error(TBADFD, env);
	env->w_term.c_lflag |= (ICANON | ECHO);
	if (tcsetattr(env->t_fd, TCSANOW, &(env->w_term)) < 0)
		term_error(TBADFD, env);
	tputs(tgetstr("cl", NULL), 1, term_write);
	tputs(tgetstr("te", NULL), 1, term_write);
	tputs(tgetstr("ve", NULL), 1, term_write);
	close(env->t_fd);
	ft_memdel((void**)&(env->a_slt));
	exit(0);
}

static void	term_init(t_env *env)
{
	char	*term;
	int		msg;

	if (!(term = getenv("TERM")))
		term_error(TNOENV, env);
	if (!isatty(STDIN_FILENO))
		term_error(TNOTTY, env);
	if ((msg = (tgetent(NULL, term))) < 1)
	{
		if (msg == 0)
			term_error(TNOENTRY, env);
		else
			term_error(TNODATABASE, env);
	}
	if ((env->t_fd = open(ttyname(STDIN_FILENO), O_RDWR)) < 0)
		term_error(TTTYNAME, env);
	if (tcgetattr(env->t_fd, &(env->w_term)) < 0)
		term_error(TBADFD, env);
}

/*
**	TCSANOW : Appliquer les modifications immediatement
**	ECHO : Effectue un echo des caracteres saisis (Ici desactive avec ~)
**	ICANON : Mode canonique du terminal (Active par defaut, desactive avec ~)
**	vi : Curseur invisible
**	cl : Efface l'ecran + Repositionne le curseur au debut
**	sc : Sauvegarder la position du curseur
**	ve : Curseur visible
*/

void		term_launch(t_env *env)
{
	term_init(env);
	env->w_term.c_lflag &= ~(ICANON | ECHO);
	env->w_term.c_cc[VMIN] = 1;
	env->w_term.c_cc[VTIME] = 0;
	if (tcsetattr(env->t_fd, TCSANOW, &(env->w_term)) < 0)
		term_error(TBADFD, env);
	tputs(tgetstr("ti", NULL), 1, term_write);
	tputs(tgetstr("vi", NULL), 1, term_write);
	tputs(tgetstr("cl", NULL), 1, term_write);
	tputs(tgetstr("sc", NULL), 1, term_write);
	signal_keep_env(env);
}
