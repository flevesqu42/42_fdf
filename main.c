/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 00:24:49 by flevesqu          #+#    #+#             */
/*   Updated: 2016/02/11 23:17:37 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			main(int ac, char **argv)
{
	t_gen	*gen;

	if (ac != 2 && ac != 4)
		error(5);
	if (!(gen = (t_gen*)malloc(sizeof(t_gen))))
		error(3);
	gen->back_color = ac == 4 ? ft_atoi(argv[2]) : 0x0;
	gen->line_color = ac == 4 ? ft_atoi(argv[3]) : 0xffffff;
	gen->fdf = acquisition(argv[1]);
	if (!(gen->mlx = mlx_init()))
		error(1);
	if (!(gen->win = mlx_new_window(gen->mlx, X, Y, ft_strrchr(argv[1], '/')
					? ft_strrchr(argv[1], '/') + 1 : argv[1])))
		error(2);
	enter_fdf(gen);
	mlx_hook(gen->win, 2, (1l << 0), key_functions, gen);
	mlx_loop(gen->mlx);
	return (0);
}

void		clear_fdf(t_fdf *fdf)
{
	fdf->zoom = 0;
	fdf->pos_x = 0;
	fdf->pos_y = 0;
	fdf->inc_y = 20;
	fdf->inc_x = 0;
	fdf->z_ratio = 20;
	fdf->rota = 0;
}

static void	key_functions_bis_2(int key, t_gen *gen)
{
	if (key == 1)
		gen->fdf->inc_y -= 1;
	else if (key == 2)
		gen->fdf->inc_x += 1;
	else if (key == 0)
		gen->fdf->inc_x -= 1;
	else if (key == 12)
		gen->fdf->rota -= 1;
	else if (key == 14)
		gen->fdf->rota += 1;
	else if (key == 83)
		gen->fdf->color_mod = 1;
	else if (key == 82)
		gen->fdf->color_mod = 0;
	else if (key == 84)
		gen->fdf->color_mod = 2;
}

static void	key_functions_bis_1(int key, t_gen *gen)
{
	if (key == 123)
		gen->fdf->pos_x -= 3 + gen->fdf->zoom;
	else if (key == 124)
		gen->fdf->pos_x += 3 + gen->fdf->zoom;
	else if (key == 125)
		gen->fdf->pos_y += 3 + gen->fdf->zoom;
	else if (key == 126)
		gen->fdf->pos_y -= 3 + gen->fdf->zoom;
	else if (key == 8)
		clear_fdf(gen->fdf);
	else if (key == 37)
		gen->fdf->z_ratio -= 1;
	else if (key == 32)
		gen->fdf->z_ratio += 1;
	else if (key == 6)
		gen->fdf->zoom += 1;
	else if (key == 7)
		gen->fdf->zoom -= 1;
	else if (key == 13)
		gen->fdf->inc_y += 1;
	else
		key_functions_bis_2(key, gen);
}

int			key_functions(int key, t_gen *gen)
{
	if (!gen || key == 53)
		exit(1);
	else if (key == 123 || key == 124 || key == 125 || key == 126 || key == 8
			|| key == 32 || key == 37 || key == 6 || key == 7 || key == 13
			|| key == 1 || key == 0 || key == 2 || key == 12 || key == 14
			|| key == 83 || key == 82 || key == 84)
	{
		key_functions_bis_1(key, gen);
		mlx_clear_window(gen->mlx, gen->win);
		enter_fdf(gen);
	}
	return (0);
}
