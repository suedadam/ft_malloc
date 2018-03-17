/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   page_size.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:26:22 by asyed             #+#    #+#             */
/*   Updated: 2018/03/17 14:12:27 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

uint8_t	chksum(void *mem)
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
		if (!(*fetched_seg = init_page(pagesize)))
			return (NULL);
	}
	mem_seg = find_space(*fetched_seg, pagesize, size);
	((t_header *)(mem_seg - sizeof(t_header)))->index = page_index;
	((t_header *)(mem_seg - sizeof(t_header)))->chksum =
				chksum(mem_seg - sizeof(t_header));
	pthread_mutex_unlock(mutex_lock);
	return (mem_seg);
}

void	*large_alloc(size_t size)
{
	void	*tmp;

	if ((tmp = mmap(NULL, size +
			sizeof(t_header), PROT_ALL, FT_MAP_ANON, -1, 0)) == MAP_FAILED)
		return (NULL);
	((t_header *)tmp)->index = LARGE_IND;
	((t_header *)tmp)->used = 1;
	return ((void *)tmp + sizeof(t_header));
}

int		get_memseg_size(uint8_t index)
{
	if (index == TINY_IND)
		return (TINY);
	else if (index == SMALL_IND)
		return (LARGE - 1);
	else if (index == LARGE_IND)
		return (LARGE);
	else
		return (0);
}
