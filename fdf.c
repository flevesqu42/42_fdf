/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 19:06:11 by flevesqu          #+#    #+#             */
/*   Updated: 2016/02/10 07:35:22 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static float	define_x(t_fdf *fdf, size_t x, size_t y)
{
	return (X / 2 - ((fdf->x / 2) - x + ((y - (fdf->y / 2))
			* (fdf->rota) / 10)) * (X / fdf->x / 2 + fdf->zoom
			- ((fdf->y - y) * (fdf->inc_y) / (fdf->y * fdf->y) * 3)
			- fabs(fdf->inc_x) / fdf->x * 15)
			+ (fdf->z[y][x] * fdf->z_ratio * 0.5 * fdf->inc_x / (fdf->x * 10))
			+ (fdf->z[y][x] * fdf->z_ratio * 0.5 * fabs(fdf->rota) * 0.03
				* fdf->inc_x / (fdf->x * 10)) + fdf->pos_x);
}

static float	define_y(t_fdf *fdf, size_t x, size_t y)
{
	return (Y / 2 - ((fdf->y / 2) - y - ((x - (fdf->x / 2))
			* (fdf->rota) / 10)) * (X / fdf->x / 2 + fdf->zoom
			+ ((fdf->x - x) * (fdf->inc_x) / (fdf->x * fdf->x) * 3)
			- fabs(fdf->inc_y) / fdf->y * 15)
			- (fdf->z[y][x] * fdf->z_ratio * 0.5 * fdf->inc_y / (fdf->y * 10))
			- (fdf->z[y][x] * fdf->z_ratio * 0.5 * fabs(fdf->rota) * 0.04
				* fdf->inc_y / (fdf->y * 10)) + fdf->pos_y);
}

static void		define_points_bis(t_gen *gen, t_xy *co, int x, int y)
{
	co->sy = define_y(gen->fdf, x, y);
	co->sx = define_x(gen->fdf, x, y);
	co->dx = x + 1 != gen->fdf->x ? define_x(gen->fdf, x + 1, y) : co->sx;
	co->dy = x + 1 != gen->fdf->x ? define_y(gen->fdf, x + 1, y) : co->sy;
	if (!gen->fdf->color_mod)
		trace_line(gen, co, gen->fdf->color[y][x], x + 1 != gen->fdf->x
				? gen->fdf->color[y][x + 1] : gen->fdf->color[y][x]);
	else if (gen->fdf->color_mod == 2)
		trace_line(gen, co, gen->line_color, gen->line_color);
	else
		trace_line(gen, co, col(gen->fdf->z[y][x]), x + 1 != gen->fdf->x
				? col(gen->fdf->z[y][x + 1]) : col(gen->fdf->z[y][x]));
	co->dx = y + 1 != gen->fdf->y ? define_x(gen->fdf, x, y + 1) : co->sx;
	co->dy = y + 1 != gen->fdf->y ? define_y(gen->fdf, x, y + 1) : co->sy;
	if (!gen->fdf->color_mod)
		trace_line(gen, co, gen->fdf->color[y][x]
			, y + 1 != gen->fdf->y
			? gen->fdf->color[y + 1][x] : gen->fdf->color[y][x]);
	else if (gen->fdf->color_mod == 2)
		trace_line(gen, co, gen->line_color, gen->line_color);
	else
		trace_line(gen, co, col(gen->fdf->z[y][x]), y + 1 != gen->fdf->y
				? col(gen->fdf->z[y + 1][x]) : col(gen->fdf->z[y][x]));
}

static void		define_points(t_gen *gen)
{
	int		x;
	int		y;
	t_xy	*co;

	y = 0;
	if (!(co = (t_xy*)malloc(sizeof(t_xy))))
		error(3);
	while (y < gen->fdf->y)
	{
		x = 0;
		while (x < gen->fdf->x)
		{
			define_points_bis(gen, co, x, y);
			x += 1;
		}
		y += 1;
	}
	free(co);
}

void			enter_fdf(t_gen *gen)
{
	if (!(gen->img = (t_img*)malloc(sizeof(t_img))))
		error(3);
	if (!(gen->img->img = mlx_new_image(gen->mlx, X, Y)))
		error(4);
	gen->img->data = mlx_get_data_addr(gen->img->img, &gen->img->bpp,
			&gen->img->sl, &gen->img->endian);
	if (gen->back_color && gen->fdf->color_mod == 2)
		back(gen);
	define_points(gen);
	mlx_put_image_to_window(gen->mlx, gen->win, gen->img->img, 0, 0);
	mlx_destroy_image(gen->mlx, gen->img->img);
}
