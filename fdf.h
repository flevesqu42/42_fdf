/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 00:36:25 by flevesqu          #+#    #+#             */
/*   Updated: 2016/02/10 06:42:05 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <math.h>
# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# define X 1600
# define Y 1000

typedef struct	s_img
{
	void	*img;
	int		bpp;
	int		sl;
	int		endian;
	char	*data;
}				t_img;

typedef struct	s_fdf
{
	float		x;
	float		y;
	float		**z;
	size_t		**color;
	float		zoom;
	float		pos_x;
	float		pos_y;
	float		z_ratio;
	float		inc_y;
	float		inc_x;
	float		color_mod;
	float		rota;
}				t_fdf;

typedef struct	s_gen
{
	int		back_color;
	int		line_color;
	t_fdf	*fdf;
	t_img	*img;
	void	*mlx;
	void	*win;
}				t_gen;

typedef struct	s_xy
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
}				t_xy;

void			enter_fdf(t_gen *mlx);
void			error(int i);
int				key_functions(int key, t_gen *gen);
t_fdf			*acquisition(char *file);
void			trace_line(t_gen *gen, t_xy *co, size_t color1, size_t color2);
void			img_pixel_put(t_img *img, int x, int y, size_t color);
void			clear_fdf(t_fdf *gen);
int				col(int z);
void			back(t_gen *gen);

#endif
