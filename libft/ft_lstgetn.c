/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstgetn.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/29 22:19:47 by flevesqu          #+#    #+#             */
/*   Updated: 2015/11/29 23:13:18 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstgetn(t_list **lst, size_t n)
{
	while ((*lst)->next && n && *lst)
	{
		*lst = (*lst)->next;
		n--;
	}
	return (*lst);
}
