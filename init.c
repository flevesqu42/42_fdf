/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/24 01:35:19 by flevesqu          #+#    #+#             */
/*   Updated: 2016/02/10 06:35:02 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		free_split(char **split)
{
	int	index;

	index = 0;
	while (split[index])
	{
		free(split[index]);
		index++;
	}
	free(split);
}

static void		define_width_and_weight(t_fdf *n, char *file)
{
	char	*line;
	int		tmp;
	int		fd;
	int		ret;
	char	**split;

	if ((fd = open(file, O_RDONLY)) == -1)
		error(6);
	ret = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		tmp = 0;
		if (!(split = ft_strsplit(line, ' ')))
			error(3);
		while (split[tmp])
			ft_isprint(*split[tmp]) ? tmp += 1 : error(10);
		n->x = n->x == 0 ? tmp : n->x;
		n->x == 0 ? error(8) : n->x;
		tmp != n->x ? error(9) : tmp;
		n->y += 1;
	}
	!n->x || !n->y ? error(8) : n->x;
	ret == -1 ? error(7) : ret;
	free_split(split);
	close(fd);
}

static void		n_fdf(int fd, t_fdf *n)
{
	char	*line;
	char	**split;
	size_t	index_1;
	size_t	index_2;
	int		ret;

	index_1 = 0;
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (!(n->z[index_1] = (float*)malloc(sizeof(float) * n->x))
			|| !(n->color[index_1] = (size_t*)malloc(sizeof(size_t) * n->x)))
			error(3);
		split = ft_strsplit(line, ' ');
		index_2 = 0;
		while (split[index_2])
		{
			n->z[index_1][index_2] = ft_atoi(split[index_2]);
			n->color[index_1][index_2] = ft_strchr(split[index_2], ',') ?
				ft_atoi(ft_strchr(split[index_2], ',') + 1) : 0x00FFFFFF;
			index_2 += 1;
		}
		index_1 += 1;
	}
	ret == -1 ? error(7) : ret;
	free_split(split);
}

t_fdf			*acquisition(char *file)
{
	t_fdf	*n;
	int		fd;

	if (!(n = (t_fdf*)malloc(sizeof(t_fdf))))
		error(3);
	n->x = 0;
	n->y = 0;
	define_width_and_weight(n, file);
	if (!(n->z = (float**)malloc(sizeof(float*) * n->y))
			|| !(n->color = (size_t**)malloc(sizeof(size_t*) * n->y)))
		error(3);
	if ((fd = open(file, O_RDONLY)) == -1)
		error(6);
	n_fdf(fd, n);
	close(fd);
	clear_fdf(n);
	return (n);
}
