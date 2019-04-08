/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_select.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 21:17:42 by rmarracc          #+#    #+#             */
/*   Updated: 2019/02/05 11:14:39 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SELECT_H
# define FT_SELECT_H

# include "libft/libft.h"
# include "libft/ft_printf/ft_printf.h"
# include <sys/ioctl.h>
# include <signal.h>
# include <stdint.h>
# include <fcntl.h>
# include <unistd.h>
# include <termios.h>
# include <termcap.h>

# define LEFT			4479771
# define RIGHT			4414235
# define SPACE			32
# define ENTER			10
# define ECHAP			27
# define BACKSPACE		127
# define DELETE			2117294875
# define UP				4283163
# define DOWN			4348699

typedef enum			e_bool
{
	FALSE,
	TRUE
}						t_bool;

typedef enum			e_error
{
	TNOTTY,
	TNOENV,
	TTTYNAME,
	TNOENTRY,
	TNODATABASE,
	TBADFD
}						t_error;

typedef struct			s_env
{
	int					t_fd;
	int32_t				col_nb;
	int32_t				a_nb;
	int32_t				a_head;
	char				**a_str;
	uint8_t				*a_slt;
	size_t				a_max;
	struct winsize		w_size;
	struct termios		w_term;
}						t_env;

typedef struct			s_opt
{
	t_bool				selected;
	t_bool				is_head;
	uint8_t				type;
	size_t				len;
	int					fd;
	int					sym;
}						t_opt;

/*
**	signal handler
*/

void					signal_handler(int val);
void					signal_suspend(void);
void					signal_continue(void);
void					signal_resize(void);
void					signal_quit(void);
t_env					*signal_keep_env(t_env *env);
void					wrapper(int val);

/*
**	terminal functions
*/

void					term_error(t_error error, t_env *env);
void					term_launch(t_env *env);
int						term_write(int t);
void					term_quit(t_env *env);

/*
**	input functions
*/

size_t					input_max_arg_len(t_env *env);
void					input_wait(t_env *env);

/*
**	input extra functions
*/

void					input_up_down(t_env *env, uint32_t end);
void					input_delete(t_env *env);

/*
**	display functions
*/

int						display_check(t_env *env);
void					display_args(t_env *env);

#endif
