/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 18:30:04 by asyed             #+#    #+#             */
/*   Updated: 2018/03/15 21:47:03 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int		space_avail(t_header *l_ptr, size_t size)
{
	t_header	*post_segs;
	size_t		avail;
	void		*tmp;

	post_segs = ((void *)l_ptr) + sizeof(t_header) + l_ptr->len;
	avail = l_ptr->len;
	while (avail < size)
	{
		if (post_segs->used)
			return (-1);
		if (!post_segs->len)
		{
			avail = size;
			break ;
		}
		if (post_segs->next_page)
		{
			if (avail + post_segs->len >= size)
				l_ptr->next_page = post_segs->next_page;
			else
				return (-1);
		}
		avail += post_segs->len;
		post_segs = ((void *)post_segs) + post_segs->len;
	}
	bzero(((void *)l_ptr) + sizeof(t_header) + l_ptr->len, avail - l_ptr->len);
	return (0);
}

void 	*realloc(void *ptr, size_t size)
{
	t_header	*l_ptr;
	void		*copy;

	if (!ptr)
		return (malloc(size));
	l_ptr = ptr - sizeof(t_header);
	if (l_ptr->len < size)
	{
		if (!l_ptr->large && size < l_ptr->max &&
			!l_ptr->next_page && !space_avail(l_ptr, size))
			return (ptr);
		copy = malloc(size);
		memcpy(copy, ptr, l_ptr->len);
		free(ptr);
		return (copy);
	}
	free(ptr);
	return (NULL);
}
