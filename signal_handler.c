/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 21:19:52 by rmarracc          #+#    #+#             */
/*   Updated: 2019/02/05 09:10:52 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
**	signal handler
*/

void		wrapper(int val)
{
	if (val == SIGTSTP)
		signal_suspend();
	else if (val == SIGCONT)
		signal_continue();
	else if (val == SIGWINCH)
		signal_resize();
	else
		signal_quit();
}

void		signal_handler(int val)
{
	while (val < 32)
	{
		if (val != SIGKILL && val != SIGSTOP)
			signal(val, wrapper);
		val++;
	}
}
