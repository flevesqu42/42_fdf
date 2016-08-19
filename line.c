/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 20:41:10 by flevesqu          #+#    #+#             */
/*   Updated: 2016/02/10 06:38:36 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			img_pixel_put(t_img *img, int x, int y, size_t color)
{
	size_t	index;

	if (y >= Y || x >= X || x < 0 || y < 0)
		return ;
	index = (y * img->sl) + x * (img->bpp / 8);
	img->data[index + 3] = (color & 0xFF000000) >> 24;
	img->data[index + 2] = (color & 0x00FF0000) >> 16;
	img->data[index + 1] = (color & 0x0000FF00) >> 8;
	img->data[index] = color & 0x000000FF;
}

static float	init_rep(float diff_x, float diff_y)
{
	float	rep;

	rep = 0;
	if ((diff_x < 0 ? -diff_x : diff_x) < (diff_y < 0 ? -diff_y : diff_y))
		rep = (diff_y / diff_x) / 2;
	else if ((diff_y < 0 ? -diff_y : diff_y) < (diff_x < 0 ? -diff_x : diff_x))
		rep = (diff_x / diff_y) / 2;
	return (rep);
}

static void		trace_line_bis(float diff_a, float diff_b, float *mod
		, float *rep)
{
	if ((diff_a < 0 ? -diff_a : diff_a) < (diff_b < 0 ? -diff_b : diff_b))
		*rep += diff_b / diff_a;
	if (*mod < diff_a)
		*mod += 1;
	else if (*mod > diff_a)
		*mod -= 1;
}

int				col(int z)
{
	if (z < 0)
		return (0x90);
	else if (z <= 50)
		return (0xff00 - (z * 0x0300));
	else if (z <= 70)
		return (0x802020 - ((z - 50) * 0x010101));
	else
		return (0xffffff);
}

void			trace_line(t_gen *gen, t_xy *co, size_t color1, size_t color2)
{
	float	x;
	float	y;
	float	rep;
	float	diff_y;
	float	diff_x;

	x = 0;
	y = 0;
	diff_y = (float)(co->sy - co->dy);
	diff_x = (float)(co->sx - co->dx);
	rep = init_rep(diff_x, diff_y);
	while (x != diff_x || y != diff_y)
	{
		img_pixel_put(gen->img, co->sx - x, co->sy - y, fabs(y) + fabs(x)
				< (fabs(diff_y) + fabs(diff_x)) / 2 ? color1 : color2);
		if (((diff_x < 0 ? -diff_x : diff_x) >= (diff_y < 0 ? -diff_y : diff_y))
				|| (y < 0 ? -y : y) >= (rep < 0 ? -rep : rep))
			trace_line_bis(diff_x, diff_y, &x, &rep);
		if (((diff_y < 0 ? -diff_y : diff_y) >= (diff_x < 0 ? -diff_x : diff_x))
				|| (x < 0 ? -x : x) >= (rep < 0 ? -rep : rep))
			trace_line_bis(diff_y, diff_x, &y, &rep);
	}
	img_pixel_put(gen->img, co->dx, co->dy, color2);
}
