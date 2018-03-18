/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_large.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 13:33:42 by asyed             #+#    #+#             */
/*   Updated: 2018/03/18 00:47:55 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	add_to_end(void **head, void *mem_seg)
{
	void	*curr_page;

	if (!(curr_page = *head))
	{
		*head = mem_seg;
		return ;
	}
	while (((t_header *)curr_page)->next_page)
	{
		curr_page = ((t_header *)curr_page)->next_page;
	}
	((t_header *)curr_page)->next_page = mem_seg;
	((t_header *)(curr_page))->chksum = chksum(mem_seg);
}

void		*alloc_large(int page_index, size_t pagesize, size_t req_len)
{
	void			**fetched_seg;
	pthread_mutex_t	*mutex_lock;
	void			*mem_seg;

	fetched_seg = &(g_pages[page_index]);
	mutex_lock = &(g_mutex[page_index]);
	pthread_mutex_lock(mutex_lock);
	mem_seg = init_page(pagesize);
	add_to_end(fetched_seg, mem_seg);
	((t_header *)(mem_seg))->index = page_index;
	((t_header *)(mem_seg))->len = req_len;
	((t_header *)(mem_seg))->chksum = chksum(mem_seg);
	pthread_mutex_unlock(mutex_lock);
	return (mem_seg + sizeof(t_header));
}
