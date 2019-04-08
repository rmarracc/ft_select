/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bs_putarraynb.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarracc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 16:50:43 by rmarracc          #+#    #+#             */
/*   Updated: 2018/11/05 16:51:01 by rmarracc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bs_putarraynb(int **grid, int len)
{
	int i;
	int j;

	if (!grid)
		return ;
	i = 0;
	while (grid[i])
	{
		j = 0;
		while (j < len)
		{
			ft_putnbr(grid[i][j]);
			ft_putstr(" ");
			j++;
		}
		ft_putendl("");
		i++;
	}
}
