/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 00:14:58 by asyed             #+#    #+#             */
/*   Updated: 2018/03/19 16:12:45 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		*init_page(size_t pagesize)
{
	void	*tmp;

	if ((tmp = mmap(NULL, pagesize, PROT_ALL, FT_MAP_ANON, -1, 0))
				== MAP_FAILED)
		return (NULL);
	return (tmp);
}

int			next_page(t_header **l_page, void **curr_page, size_t pagesize)
{
	void	*tmp;

	if (!(tmp = init_page(pagesize)))
		return (-1);
	(*l_page)->next_page = tmp;
	(*l_page)->chksum = chksum(*l_page);
	*curr_page = tmp;
	(*l_page) = (t_header *)(*curr_page);
	return (0);
}

int			align_pagesize(size_t x, int large)
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

static int	in_large(void *ptr, int page_index)
{
	void	*head;
	void	*l_ptr;
	size_t	pagesize;

	if (page_index == LARGE_IND)
	{
		if (!(head = g_pages[LARGE_IND]))
			return (0);
		l_ptr = head;
		pagesize = align_pagesize(((t_header *)head)->len, 1);
		while (l_ptr && l_ptr < head + pagesize)
		{
			if (ptr >= head && ptr <= head + pagesize)
				return (1);
			head = ((t_header *)l_ptr)->next_page;
			l_ptr = head;
		}
	}
	return (0);
}

int			non_allocated(void *ptr, int page_index)
{
	void	*head;
	void	*l_ptr;
	size_t	pagesize;

	if (page_index < LARGE_IND)
	{
		head = g_pages[page_index];
		l_ptr = head;
		pagesize = align_pagesize(get_memseg_size(page_index), 0);
		while (l_ptr && l_ptr < (head + pagesize))
		{
			if (ptr >= head && ptr < (head + pagesize))
				return (1);
			if (((t_header *)l_ptr)->next_page)
			{
				head = ((t_header *)l_ptr)->next_page;
				l_ptr = head;
				continue ;
			}
			l_ptr = OFFP_HEADER(((t_header *)l_ptr));
		}
		return (non_allocated(ptr, page_index + 1));
	}
	return (in_large(ptr, page_index));
}
