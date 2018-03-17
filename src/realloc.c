/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 18:30:04 by asyed             #+#    #+#             */
/*   Updated: 2018/03/17 03:47:15 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int		space_avail(t_header *l_ptr, size_t size)
{
	t_header	*post_segs;
	size_t		avail;

	post_segs = ((void *)l_ptr) + sizeof(t_header) + l_ptr->len;
	avail = l_ptr->len;
	while (avail < size)
	{
		if (post_segs->used)
			return (1);
		if (!post_segs->len &&
			!post_segs->next_page)
		{
			avail = size;
			break ;
		}
		if (post_segs->next_page)
		{
			if (avail + post_segs->len >= size)
				l_ptr->next_page = post_segs->next_page;
			else
				return (1);
		}
		avail += post_segs->len;
		post_segs = ((void *)post_segs) + post_segs->len;
	}
	bzero(((void *)l_ptr) + sizeof(t_header) + l_ptr->len, avail - l_ptr->len);
	l_ptr->len = avail;
	return (0);
}

void	*realloc(void *ptr, size_t size)
{
	t_header	*l_ptr;
	void		*copy;
	size_t		max;

	if (!ptr || !valid_chksum(ptr - sizeof(t_header)))
		return (malloc(size));
	l_ptr = ptr - sizeof(t_header);
	max = get_memseg_size(l_ptr->index);
	if (l_ptr->len < size)
	{
		if (l_ptr->index != LARGE_IND && size < max &&
			!l_ptr->next_page && !space_avail(l_ptr, size))
		{
			l_ptr->chksum = chksum(l_ptr);
			return (ptr);
		}
		copy = malloc(size);
		memcpy(copy, ptr, l_ptr->len);
		free(ptr);
		return (copy);
	}
	else if (size <= l_ptr->len && size > 0)
		return (ptr);
	free(ptr);
	return (NULL);
}
