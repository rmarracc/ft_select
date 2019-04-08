/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 21:19:52 by rmarracc          #+#    #+#             */
/*   Updated: 2019/02/05 09:10:52 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_select.h"

/*
**	main
*/

int			main(int argc, char **argv)
{
	t_env	env;

	if (argc < 2)
		return (0);
	env.a_nb = argc - 1;
	env.a_str = argv + 1;
	env.a_head = 0;
	if (!(env.a_slt = (uint8_t*)ft_memalloc(sizeof(uint8_t) * env.a_nb)))
		return (0);
	signal_handler(1);
	term_launch(&env);
	input_wait(&env);
	term_quit(&env);
	return (0);
}
