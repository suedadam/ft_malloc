/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:37:08 by asyed             #+#    #+#             */
/*   Updated: 2018/04/10 01:43:20 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_tree			g_segments;

void		*resize_segment(t_header **seg, size_t size)
{
	t_header	*ret;

	if (!(ret = *seg))
		return (NULL);
	if (((void *)ret + sizeof(t_header) + size) <
		((void *)((t_header *)ret)->page_start) +
		align_pagesize(index2size(index_calc(size)), 0) &&
		kill_cleaner(ret) == EXIT_SUCCESS)
	{
		if (*seg)
			((t_header *)(((void *)ret) + sizeof(t_header) + size))->next = (*seg)->next;
		*seg = ((void *)ret) + sizeof(t_header) + size;
		ret->len = size;
		ret->used = 1;
		ret->index = index_calc(size);
		ret->chksum = chksum(ret);
		(*seg)->page_start = ((t_header *)ret)->page_start;
		return (((void *)ret) + sizeof(t_header));
	}
	else
		return (new_page(size));
}

size_t		align_pagesize(size_t x, int large)
{
	static int	sys_size = 0;
	size_t		page;

	if (!sys_size)
		sys_size = getpagesize();
	if (large)
		page = x + sizeof(t_header);
	else
		page = PAGESIZE(x);
	return (page + (page % sys_size));
}

void		*new_page(size_t size)
{
	t_header	*tmp;
	uint8_t		index;

	index = index_calc(size);
	if ((tmp = mmap(NULL, align_pagesize(index2size(index), 0), PROT_ALL, FT_MAP_ANON, -1, 0))
				== MAP_FAILED)
		return (NULL);
	tmp->page_start = tmp;
	tmp->len = size;
	tmp->used = 1;
	tmp->index = index;
	tmp->chksum = chksum(tmp);
	((t_header *)(((void *)tmp) + sizeof(t_header) + size))->next = g_segments.avail_segs[0];
	g_segments.avail_segs[0] = (((void *)tmp) + sizeof(t_header) + size);
	((t_header *)g_segments.avail_segs[0])->page_start = tmp;
	return (((void *)tmp) + sizeof(t_header));
}

void	*large_allocation(size_t size)
{
	t_header	*tmp;

	if ((tmp = mmap(NULL, align_pagesize(size, 1), PROT_ALL, FT_MAP_ANON, -1, 0))
				== MAP_FAILED)
	{
		printf("Failed to mmap (%s)\n", strerror(errno));
		return (NULL);
	}
	tmp->page_start = tmp;
	tmp->len = align_pagesize(size, 1);
	tmp->used = 1;
	tmp->index = 2;
	tmp->chksum = chksum(tmp);
	return ((void *)tmp + sizeof(t_header));
}

void		*malloc(size_t size)
{
	t_header	*ptr;

	if (!size)
		return (g_segments.avail_segs[size]);
	if (size < LARGE)
	{
		if (!(g_segments.avail_segs[size]))
		{
			if (g_segments.avail_segs[0])
				return (resize_segment(&(g_segments.avail_segs[0]), size));
			return (new_page(size));
		}
		ptr = g_segments.avail_segs[size];
		if (kill_cleaner(ptr) == EXIT_FAILURE)
			return (new_page(size));
		if (ptr)
			g_segments.avail_segs[size] = ptr->next;
		else
			g_segments.avail_segs[size] = NULL;
		ptr->chksum = chksum(ptr);
		return ((void *)ptr + sizeof(t_header));
	}
	return (large_allocation(size));
}
