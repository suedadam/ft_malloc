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

size_t __attribute__((always_inline))	guess_pagesize(uint8_t pageid)
{
	static int	tiny = 0;
	static int	small = 0;

	if (!tiny)
	{
		tiny = align_pagesize(TINY, 0);
		small = align_pagesize(LARGE, 0);
	}
	if (pageid == TINY_IND)
		return (tiny);
	return (small);
}

void  __attribute__((always_inline))	*resize_segment(t_header **seg, size_t size)
{
	t_header	*ret;
	uint8_t		index;

	if (!(ret = *seg))
		return (NULL);
	index = index_calc(size);
	if (((void *)ret + sizeof(t_header) + size) <
		((void *)((t_header *)ret)->page_start) + guess_pagesize(index) &&
		kill_cleaner(ret->pageid) == EXIT_SUCCESS)
	{
		__builtin_prefetch(ret, 1);
		ret->len = size;
		ret->used = 1;
		ret->index = index;
		ret->chksum = chksum(ret);
		((t_header *)(((void *)ret) + sizeof(t_header) + size))->next = (*seg)->next;
		*seg = ((void *)ret) + sizeof(t_header) + size;
		(*seg)->page_start = ((t_header *)ret)->page_start;
		(*seg)->pageid = ((t_header *)ret)->pageid;
		return (((void *)ret) + sizeof(t_header));
	}
	return (new_page(size));
}

size_t __attribute__((always_inline))	align_pagesize(size_t x, int large)
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

void __attribute__((always_inline))		*new_page(size_t size)
{
	static uint16_t	pageid = 0;
	t_header		*tmp;
	uint8_t			index;

	if (pageid == (MAXPAGES - 1))
		return (NULL);
	index = index_calc(size);
	if ((tmp = mmap(NULL, guess_pagesize(index), PROT_ALL, FT_MAP_ANON, -1, 0))
				== MAP_FAILED)
		return (NULL);
	__builtin_prefetch(tmp, 1);
	tmp->page_start = tmp;
	tmp->len = size;
	tmp->used = 1;
	tmp->index = index;
	tmp->chksum = chksum(tmp);
	tmp->pageid = pageid;
	((t_header *)(((void *)tmp) + sizeof(t_header) + size))->next = g_segments.avail_segs[0];
	g_segments.avail_segs[0] = (((void *)tmp) + sizeof(t_header) + size);
	((t_header *)g_segments.avail_segs[0])->page_start = tmp;
	((t_header *)g_segments.avail_segs[0])->pageid = pageid++;
	return (((void *)tmp) + sizeof(t_header));
}

void __attribute__((always_inline))		*large_allocation(size_t size)
{
	t_header	*tmp;
	size_t		pagesize;

	pagesize = align_pagesize(size, 1);
	if ((tmp = mmap(NULL, pagesize, PROT_ALL, FT_MAP_ANON, -1, 0))
				== MAP_FAILED)
		return (NULL);
	tmp->page_start = tmp;
	tmp->len = pagesize;
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
		if (kill_cleaner(ptr->pageid) == EXIT_FAILURE)
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
