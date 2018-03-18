/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 00:14:58 by asyed             #+#    #+#             */
/*   Updated: 2018/03/18 01:48:14 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*init_page(size_t pagesize)
{
	void	*tmp;

	if ((tmp = mmap(NULL, pagesize, PROT_ALL, FT_MAP_ANON, -1, 0))
				== MAP_FAILED)
		return (NULL);
	return (tmp);
}

int		next_page(t_header **l_page, void **curr_page, size_t pagesize)
{
	void	*tmp;

	if (!(tmp = init_page(pagesize)))
		return (-1);
	(*l_page)->next_page = tmp;
	*curr_page = tmp;
	(*l_page) = (t_header *)(*curr_page);
	return (0);
}

/*
** # define PAGESIZE(x) ((x + sizeof(t_header)) * MAX_PER_PAGE)
*/

int		align_pagesize(size_t x, int large)
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

static int 	in_large(void *ptr)
{
	void	*head;
	void	*l_ptr;
	size_t	pagesize;

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
	return (0);
}

int		non_allocated(void *ptr, int page_index)
{
	void	*head;
	void	*l_ptr;
	size_t	pagesize;

	if (page_index <= LARGE_IND)
	{
		if (page_index == LARGE_IND)
			return (in_large(ptr));
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
			l_ptr = l_ptr + ((t_header *)l_ptr)->len + sizeof(t_header);
		}
		return (non_allocated(ptr, page_index + 1));
	}
	return (0);
}

int		valid_chksum(void *l_ptr)
{
	uint8_t		sum;
	size_t		i;
	void		*increment;
	t_header	copy;

	sum = 0;
	i = 0;
	if (!non_allocated(l_ptr, 0))
		return (0);
	ft_memcpy(&copy, l_ptr, sizeof(t_header));
	copy.chksum = 0;
	increment = &copy;
	while (i++ < sizeof(t_header))
	{
		sum += *(unsigned char *)increment;
		increment++;
	}
	return (sum == ((t_header *)l_ptr)->chksum);
}
