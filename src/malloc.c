/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:37:08 by asyed             #+#    #+#             */
/*   Updated: 2018/03/18 03:34:21 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			*g_pages[3] = {NULL, NULL, NULL};
pthread_mutex_t	g_mutex[3] = {
	PTHREAD_MUTEX_INITIALIZER,
	PTHREAD_MUTEX_INITIALIZER,
	PTHREAD_MUTEX_INITIALIZER
};

static int	finite_block(void **curr_page, t_header **l_page,
						size_t req_len, size_t pagesize)
{
	if ((*l_page)->len >= req_len)
	{
		(*l_page)->used = 1;
		return (0);
	}
	else if ((*l_page)->next_page)
	{
		*curr_page = (*l_page)->next_page;
		*l_page = (t_header *)(*curr_page);
	}
	else if ((((void *)(*l_page)) + (*l_page)->len) < (*curr_page + pagesize))
		*l_page = ((void *)(*l_page)) + (*l_page)->len;
	else
		next_page(l_page, curr_page, pagesize);
	return (1);
}

static int	infinite_block(void **curr_page, t_header **l_page,
						size_t req_len, size_t pagesize)
{
	void	*void_page;

	void_page = ((void *)(*l_page)) + sizeof(t_header);
	if ((void_page + req_len) <= (*curr_page + pagesize))
	{
		(*l_page)->used = 1;
		(*l_page)->len = req_len;
		void_page = *l_page;
		if ((void_page + (*l_page)->len + sizeof(t_header))
			<= (*curr_page + pagesize - sizeof(t_header)))
		{
			((t_header *)(void_page + sizeof(t_header) +
				(*l_page)->len))->next_page = (*l_page)->next_page;
			(*l_page)->next_page = NULL;
		}
		return (0);
	}
	else if ((*l_page)->next_page)
	{
		*curr_page = (*l_page)->next_page;
		*l_page = (t_header *)(*curr_page);
		return (1);
	}
	next_page(l_page, curr_page, pagesize);
	return (1);
}

int			used_seg(t_header **l_page, void **curr_page, size_t pagesize)
{
	if ((*l_page)->next_page)
	{
		*curr_page = (*l_page)->next_page;
		*l_page = (t_header *)(*curr_page);
		return (1);
	}
	if (((void *)(*l_page)) + (*l_page)->len + sizeof(t_header) >=
		(*curr_page + pagesize))
	{
		next_page(l_page, curr_page, pagesize);
		return (1);
	}
	return (0);
}

void		*find_space(void *curr_page, size_t pagesize, size_t req_len)
{
	t_header	*l_page;

	l_page = (t_header *)curr_page;
	while (l_page && (void *)l_page < (curr_page + pagesize))
	{
		if (!l_page->used)
		{
			l_page->page_start = curr_page;
			if (!l_page->len)
			{
				if (infinite_block(&curr_page, &l_page, req_len, pagesize))
					continue ;
			}
			else if (finite_block(&curr_page, &l_page, req_len, pagesize))
				continue ;
			return ((void *)l_page);
		}
		if (used_seg(&l_page, &curr_page, pagesize))
			continue ;
		l_page = (void *)l_page + l_page->len + sizeof(t_header);
	}
	return (NULL);
}

void		*malloc(size_t size)
{
	if (size == 0)
		size = 1;
	if (size <= TINY)
		return (size_spacer(TINY_IND, align_pagesize(TINY, 0), size));
	if (size > TINY && size < LARGE)
		return (size_spacer(SMALL_IND, align_pagesize(LARGE, 0), size));
	return (alloc_large(LARGE_IND,
			align_pagesize(size, 1), size));
}
