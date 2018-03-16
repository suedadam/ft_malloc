/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:26:22 by asyed             #+#    #+#             */
/*   Updated: 2018/03/15 23:37:43 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*size_spacer(int page_index, size_t pagesize, size_t size)
{
	void			**fetched_seg;
	pthread_mutex_t	*mutex_lock;
	void			*mem_seg;

	fetched_seg = &(g_pages[page_index]);
	mutex_lock = &(g_mutex[page_index]);
	pthread_mutex_lock(mutex_lock);
	if (!*fetched_seg)
	{
		if ((*fetched_seg = mmap(NULL, pagesize, PROT_ALL, FT_MAP_ANON, -1, 0)) == MAP_FAILED)
			return (NULL);
	}
	mem_seg = find_space(*fetched_seg, pagesize, size);
	((t_header *)(mem_seg - sizeof(t_header)))->max = ((pagesize / 100) - sizeof(t_header));
	pthread_mutex_unlock(mutex_lock);
	return (mem_seg);
}

void	*large_alloc(size_t size)
{
	void	*tmp;

	if ((tmp = mmap(NULL, size + sizeof(t_header), PROT_ALL, FT_MAP_ANON, -1, 0)) == MAP_FAILED)
		return (NULL);
	((t_header *)tmp)->mem_seg = tmp + sizeof(t_header);
	((t_header *)tmp)->large = 1;
	((t_header *)tmp)->used = 1;
	return (((t_header *)tmp)->mem_seg);
}
