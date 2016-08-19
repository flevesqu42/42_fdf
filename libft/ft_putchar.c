/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 06:42:25 by flevesqu          #+#    #+#             */
/*   Updated: 2016/01/21 18:58:42 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	putchar(char c)
{
	write(1, &c, 1);
}

void		ft_putchar(int i)
{
	if (i < 0x80)
		write(1, &i, 1);
	else if (i < 0x800)
	{
		putchar(i >> 6 | 0xC0);
		putchar((i & 0xBF) | 0x80);
	}
	else if (i < 0x10000)
	{
		putchar(i >> 12 | 0xE0);
		putchar(((i >> 6) & 0xBF) | 0x80);
		putchar((i & 0xBF) | 0x80);
	}
	else
	{
		putchar(i >> 18 | 0xF0);
		putchar(((i >> 12) & 0xBF) | 0x80);
		putchar(((i >> 6) & 0xBF) | 0x80);
		putchar((i & 0xBF) | 0x80);
	}
}
