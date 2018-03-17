/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:55:09 by asyed             #+#    #+#             */
/*   Updated: 2018/03/17 05:33:45 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	flip_page(t_header **l_page, void **curr_page, size_t pagesize)
{
	while (((void *)*l_page) < (*curr_page + pagesize))
	{
		if ((*l_page)->next_page || !(*l_page)->len ||
			((void *)(*l_page)) + (*l_page)->len >= (*curr_page + pagesize))
		{
			*curr_page = (*l_page)->next_page;
			*l_page = *curr_page;
			return ;
		}
		*l_page = ((void *)(*l_page)) + (*l_page)->len;
	}
}

void	tear_page(t_header **l_page, void **curr_page, size_t pagesize, int page_index)
{
	void	*tmp;

	tmp = *curr_page;
	flip_page(l_page, curr_page, pagesize);
	if (page_index == LARGE_IND)
		munmap(tmp, align_pagesize(((t_header *)(*l_page))->len + sizeof(t_header)));
	else
		munmap(tmp, pagesize);
}

void	look_through(void **head_page, size_t pagesize, int page_index)
{
	t_header	*l_page;
	void		*curr_page;

	curr_page = *head_page;
	l_page = (void *)curr_page;
	while (l_page && (void *)l_page < (curr_page + pagesize))
	{
		if (l_page->used)
			flip_page(&l_page, &curr_page, pagesize);
		else if (!l_page->len || l_page->next_page
			|| (void *)l_page + l_page->len >= (curr_page + pagesize))
		{
			if (*head_page == curr_page)
			{
				tear_page(&l_page, &curr_page, pagesize, page_index);
				*head_page = curr_page;
			}
			else
				tear_page(&l_page, &curr_page, pagesize, page_index);
		}
		else
			l_page = (void *)l_page + l_page->len;
	}
}

void	cleaning_lady(int *clean_up, int page_index)
{
	if (page_index < LARGE_IND)
	{
		pthread_mutex_lock(&(g_mutex[page_index]));
		look_through(&(g_pages[page_index]),
					align_pagesize(get_memseg_size(page_index)), page_index);
		pthread_mutex_unlock(&(g_mutex[page_index]));
		cleaning_lady(clean_up, page_index + 1);		
	}
	else
		*clean_up = 0;
}

void	free(void *ptr)
{
	static int	clean_up = 0;
	t_header	*l_ptr;

	if (!ptr)
		return ;
	l_ptr = ptr - sizeof(t_header);
	if (!valid_chksum(l_ptr))
		return ;
	pthread_mutex_lock(&(g_mutex[l_ptr->index]));
	l_ptr->used = 0;
	bzero(ptr, l_ptr->len);
	pthread_mutex_unlock(&(g_mutex[l_ptr->index]));
	if (clean_up++ == CLEAN_INTERVAL)
		cleaning_lady(&clean_up, 0);
}
