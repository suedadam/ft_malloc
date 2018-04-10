/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:37:08 by asyed             #+#    #+#             */
/*   Updated: 2018/04/09 22:35:09 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

t_tree			g_segments;

/*
** Use this. How do you initialize all of them...?
*/

pthread_mutex_t	g_mutex[LARGE + 1] = {
	PTHREAD_MUTEX_INITIALIZER
};

static inline __attribute__((always_inline)) int		kill_cleaner(t_header *mem)
{
	if (pageid[mem->pageid])
	{
		if (pageid[mem->pageid] == (void *)-1)
			return (EXIT_FAILURE);
		pthread_cancel(pageid[mem->pageid]);
		pageid[mem->pageid] = NULL;
	}
	return (EXIT_SUCCESS);
}

static inline __attribute__((always_inline)) uint8_t	chksum(void *mem)
{
	uint8_t		sum;
	size_t		i;

	sum = 0;
	i = 0;
	((t_header *)mem)->chksum = 0;
	while (i++ < sizeof(t_header))
	{
		sum += *(unsigned char *)mem;
		mem++;
	}
	return (sum);
}

static inline __attribute__((always_inline)) int	index_calc(size_t size)
{
	if (size < TINY)
		return (0);
	else if (size < LARGE)
		return (1);
	else
		return (2);
}

static inline __attribute__((always_inline)) int	index2size(uint8_t index)
{
	if (index == 1)
		return (TINY);
	else
		return (LARGE);
}

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
	((t_header *)tmp)->page_start = tmp;
	((t_header *)tmp)->len = size;
	((t_header *)tmp)->used = 1;
	((t_header *)tmp)->index = index_calc(size);
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
