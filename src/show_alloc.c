/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 12:35:41 by asyed             #+#    #+#             */
/*   Updated: 2018/03/17 14:40:53 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		print_pagesegs(int page_index, size_t *total)
{
	void		*curr_page;
	t_header	*l_page;
	int			pagesize;

	curr_page = g_pages[page_index];
	l_page = (t_header *)curr_page;
	pagesize = align_pagesize(get_memseg_size(page_index));
	while (l_page && (void *)l_page < (curr_page + pagesize))
	{
		if (l_page->used)
		{
			printf("%p - %p : %zu bytes\n", (void *)l_page +
				sizeof(t_header), (void *)l_page +
				sizeof(t_header) + l_page->len, l_page->len);
			*total += l_page->len;
		}
		if (l_page->next_page || OFFP_HEADER(l_page) > curr_page + pagesize)
		{
			flip_page(&l_page, &curr_page, pagesize);
			continue ;
		}
		l_page = (void *)l_page + l_page->len + sizeof(t_header);
	}
	print_pageheader(page_index + 1, total);
}

static void	print_large(size_t *total)
{
	void		*curr_page;
	t_header	*l_page;

	if (!(curr_page = g_pages[LARGE_IND]))
		return ;
	while (curr_page)
	{
		l_page = (t_header *)curr_page;
		printf("%p - %p : %zu bytes\n", (void *)l_page +
			sizeof(t_header), (void *)l_page + sizeof(t_header) +
				l_page->len, l_page->len);
		*total += l_page->len;
		curr_page = l_page->next_page;
	}
}

void		print_pageheader(int page_index, size_t *total)
{
	if (page_index > LARGE_IND)
		return ;
	if (page_index == TINY_IND)
		printf("TINY :\n");
	else if (page_index == SMALL_IND)
		printf("SMALL :\n");
	else if (page_index == LARGE_IND)
		printf("LARGE:\n");
	pthread_mutex_lock(&(g_mutex[page_index]));
	if (page_index == LARGE_IND)
		print_large(total);
	else
		print_pagesegs(page_index, total);
	pthread_mutex_unlock(&(g_mutex[page_index]));
}

void		show_alloc_mem(void)
{
	size_t	total;

	total = 0;
	print_pageheader(0, &total);
	printf("Total : %zu bytes\n", total);
}
