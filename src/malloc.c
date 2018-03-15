/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:37:08 by asyed             #+#    #+#             */
/*   Updated: 2018/03/15 14:56:41 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void		*find_space(void *curr_page, size_t pagesize, size_t req_len)
{
	t_header	*l_page;
	void		*tmp;

	l_page = (t_header *)curr_page;
	while ((void *)l_page < (curr_page + pagesize))
	{
		if (!(l_page->used))
		{
			if (!l_page->mem_seg)
				l_page->mem_seg = l_page + sizeof(t_header);
			if (!l_page->page_start)
				l_page->page_start = curr_page;
			if (!l_page->len)
			{
				if ((void *)(l_page->mem_seg + req_len) < (curr_page + pagesize))
				{
					l_page->used = 1;
					l_page->len = req_len;
					((t_header *)(l_page + l_page->len))->next_page = l_page->next_page;
					return (l_page->mem_seg);
				}
				else if (l_page->next_page)
				{
					curr_page = l_page->next_page;
					l_page = (t_header *)curr_page;
					continue ;
				}
				else
				{
					if ((tmp = mmap(NULL, pagesize, PROT_ALL, FT_MAP_ANON, -1, 0)) == MAP_FAILED)
					{
						printf("{48} Errno = %s\n", strerror(errno));
						return (NULL);
					}
					l_page->next_page = tmp;
					curr_page = tmp;
					l_page = (t_header *)curr_page;
					continue ;
				}				
			}
			else
			{
				if (l_page->len >= req_len)
				{
					l_page->used = 1;
					return (l_page->mem_seg);
				}
				else if ((void *)(l_page + l_page->len) < (curr_page + pagesize))
				{
					l_page += l_page->len;
					continue ;
				}
				else
				{
					if ((tmp = mmap(NULL, pagesize, PROT_ALL, FT_MAP_ANON, -1, 0)) == MAP_FAILED)
					{
						printf("{73} Errno = %s\n", strerror(errno));
						return (NULL);
					}
					l_page->next_page = tmp;
					curr_page = tmp;
					l_page = (t_header *)curr_page;
					continue ;
				}
			}
		}
		else
			l_page += l_page->len;			
	}
	printf("I'm broken\n");
	exit(-1);
}

void 		*malloc(size_t size)
{
	void			**fetched_seg;
	pthread_mutex_t	*mutex_lock;
	void			*mem_seg;

	if (size <= TINY)
	{
		fetched_seg = &(g_pages[0]);
		mutex_lock = &(g_mutex[0]);
		if (!*fetched_seg)
		{
			if ((*fetched_seg = mmap(*fetched_seg, PAGESIZE(TINY), PROT_ALL, FT_MAP_ANON, -1, 0)) == MAP_FAILED)
			{
				printf("{104} Errno = %s\n", strerror(errno));
				return (NULL);
			}
		}
		pthread_mutex_lock(mutex_lock);
		mem_seg = find_space(*fetched_seg, PAGESIZE(TINY), size);
		pthread_mutex_unlock(mutex_lock);
		return (mem_seg);
	}
	return (NULL);
}

int		main(void)
{
	int	*test;

	if (!(test = malloc(sizeof(int))))
	{
		printf("Fail bitch\n");
		return (-1);
	}
	printf("%p\n", test);
	*test = 12;
}