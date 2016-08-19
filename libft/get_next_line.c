/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/17 04:48:24 by flevesqu          #+#    #+#             */
/*   Updated: 2016/02/10 01:47:07 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		*ft_strscat(char *s1, char *s2)
{
	char	*new;
	size_t	index;

	index = 0;
	if (!(new = (char*)malloc(sizeof(char)
					* (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[index])
	{
		new[index] = s1[index];
		index++;
	}
	while (*s2)
	{
		new[index] = *s2;
		index++;
		s2 += 1;
	}
	new[index] = '\0';
	free(s1);
	return (new);
}

static t_gnl	*new_gnl(const int fd)
{
	t_gnl	*new;

	if (!(new = (t_gnl*)malloc(sizeof(t_gnl))))
		return (NULL);
	new->fd = fd;
	new->str = NULL;
	new->next = NULL;
	return (new);
}

static int		split_buffers(t_gnl *save, char **line)
{
	char	buffer[BUFF_SIZE + 1];
	char	*endline;
	int		ret;

	endline = NULL;
	while (!endline && (ret = read(save->fd, buffer, BUFF_SIZE)) > 0)
	{
		buffer[ret] = '\0';
		if ((endline = ft_strchr(buffer, 0x0a)))
		{
			*endline = '\0';
			if (!(save->str = ft_strdup(endline + 1)))
				return (-1);
		}
		if (*line)
			if (!(*line = ft_strscat(*line, buffer)))
				return (-1);
		if (!*line)
			if (!(*line = ft_strdup(buffer)))
				return (-1);
	}
	return (ret);
}

static int		split_save(t_gnl *save, char **line)
{
	char	*endline;

	*line = NULL;
	if (save->str)
	{
		if ((endline = ft_strchr(save->str, 0x0a)))
		{
			*endline = '\0';
			if (!(*line = ft_strdup(save->str)))
				return (-1);
			if (!(save->str = ft_strdup(endline + 1)))
				return (-1);
		}
		else
		{
			if (!(*line = ft_strdup(save->str)))
				return (-1);
			free(save->str);
			save->str = NULL;
		}
	}
	return (save->str ? 1 : 0);
}

int				get_next_line(const int fd, char **line)
{
	static t_gnl	*first = NULL;
	t_gnl			*current;
	int				sret;
	int				bret;

	if (!first)
		first = new_gnl(fd);
	current = first;
	while (current->next && current->fd != fd)
		current = current->next;
	if (current->fd != fd)
	{
		current->next = new_gnl(fd);
		current = current->next;
	}
	if (!line || (sret = split_save(current, line)) == -1)
		return (-1);
	if (sret == 0)
		if ((bret = split_buffers(current, line)) == -1)
			return (-1);
	if (*line && !(**line) && !bret)
		ft_strdel(line);
	return (*line ? 1 : 0);
}
