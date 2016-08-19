/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/10 06:39:30 by flevesqu          #+#    #+#             */
/*   Updated: 2016/02/10 06:43:59 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	back(t_gen *gen)
{
	int	x;
	int	y;

	y = 0;
	while (y < Y)
	{
		x = 0;
		while (x < X)
		{
			img_pixel_put(gen->img, x, y, gen->back_color);
			x += 1;
		}
		y += 1;
	}
}

void	error(int i)
{
	if (i == 1)
		ft_putstr("Error : mlx_init() fail.\n");
	else if (i == 2)
		ft_putstr("Error : mlx_new_window() fail.\n");
	else if (i == 3)
		ft_putstr("Error : malloc() fail.\n");
	else if (i == 4)
		ft_putstr("Error : mlx_new_image() fail.\n");
	else if (i == 5)
		ft_putstr("Usage : ./fdf <filename> <back_color> <line_color>\n");
	else if (i == 6)
		ft_putstr("No file\n");
	else if (i == 7)
		ft_putstr("Error : get_next_line() fail.\n");
	else if (i == 8)
		ft_putstr("No data\n");
	else if (i == 9)
		ft_putstr("Found wrong line lenght. Exiting.\n");
	else if (i == 10)
		ft_putstr("Bad file\n");
	exit(1);
}
