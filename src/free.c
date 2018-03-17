/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:55:09 by asyed             #+#    #+#             */
/*   Updated: 2018/03/16 15:47:11 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*flip_page(t_header *mem_seg, void *curr_page, int pagemax)
{
	void	*upper_bound;

	upper_bound = mem_seg->page_start + pagemax;
	while ((void *)mem_seg < upper_bound)
	{
		if (mem_seg->next_page || !mem_seg->len)
		{
			// printf("Flipped page\n");
			// printf("Returned (%d %d) %p\n", mem_seg->next_page, !mem_seg->len, mem_seg->next_page);
			return (mem_seg->next_page);
		}
		mem_seg = (void *)mem_seg + mem_seg->len;
	}
	return (NULL);
}

void	update_last(t_header *curr, void *next, int pagemax)
{
	void	*upper_bound;

	upper_bound = curr->page_start + pagemax;
	while ((void *)curr < upper_bound)
	{
		if (curr->next_page || !curr->len)
		{
			curr->next_page = next;
			return ;
		}
		curr = (void *)curr + curr->len;
	}
}

void	*delete_page(void *prev, t_header *mem_seg, void *curr_page, int pagemax)
{
	void	*next;

	next = flip_page(mem_seg, curr_page, pagemax);
	if (prev)
		update_last(prev, next, pagemax);
	munmap(curr_page, pagemax);
	if (!prev)
		return (next);
	else
		return (NULL);
}

/*
** Never getting delete_page, need to test more why.
*/

void	cleaning_lady(int *clean_up, int page_index)
{
	void		**curr_page;
	t_header	*l_page;
	void		*tmp;
	int			pagemax;

	if (page_index < 2)
	{
		pthread_mutex_lock(&(g_mutex[page_index]));
		// Insert solution here... (lol jokes)
		curr_page = &(g_pages[page_index]); // Fix to double pointer
		l_page = (t_header *)curr_page;
		// tmp = *curr_page;
		tmp = NULL;
		pagemax = PAGESIZE(get_memseg_size(l_page->index));
		while ((void *)l_page < (*curr_page + pagemax))
		{
			printf("{DEL} %p len = %zu\n", *curr_page, l_page->len);
			if (l_page->used)
			{
				printf("wat\n");
				tmp = *curr_page;
				if (!(*curr_page = flip_page(l_page, *curr_page, pagemax)))
					break ;
				l_page = (t_header *)curr_page;
			}
			else if (!l_page->len || l_page->next_page ||
					(((void *)l_page + l_page->len) >= (*curr_page + pagemax)))
			{
				// printf("Getting to delete one. %p tmp = %p\n", *curr_page, tmp);
				if (!tmp || (tmp = delete_page(tmp, l_page, *curr_page, pagemax)))
					*curr_page = tmp;
				// printf("*curr_page = %p\n", *curr_page);
				break ;
			}
			else
			{
				printf("hmmm\n");
				l_page = (void *)l_page + l_page->len;
			}
		}
		pthread_mutex_unlock(&(g_mutex[page_index]));
		cleaning_lady(clean_up, page_index + 1);
	}
	else
		*clean_up = 0;
}

void 	free(void *ptr)
{
	static int	clean_up = 0;
	t_header	*l_ptr;

	if (!ptr)
		return ;
	l_ptr = ptr - sizeof(t_header);
	if (l_ptr->index == LARGE_IND)
		munmap(l_ptr, l_ptr->len + sizeof(t_header));
	else
	{
		pthread_mutex_lock(&g_mutex[0]);
		pthread_mutex_lock(&g_mutex[1]);
		pthread_mutex_lock(&g_mutex[2]);
		l_ptr->used = 0;
		bzero(ptr, l_ptr->len);
		pthread_mutex_unlock(&g_mutex[0]);
		pthread_mutex_unlock(&g_mutex[1]);
		pthread_mutex_unlock(&g_mutex[2]);		
	}
	// if (clean_up++ == CLEAN_INTERVAL)
		// cleaning_lady(&clean_up, 0);
}
