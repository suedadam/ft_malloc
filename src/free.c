/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 16:19:12 by asyed             #+#    #+#             */
/*   Updated: 2018/04/10 01:30:56 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	remove_dangling(t_header **segs, void *match)
{
	t_header *ptr;
	t_header *prev;

	prev = NULL;
	ptr = *segs;
	while (ptr)
	{
		if (ptr->page_start == match)
		{
			if (ptr == *segs)
				*segs = ptr->next;
			if (prev)
				prev->next = ptr->next;
		}
		else
			prev = ptr;
		ptr = ptr->next;
	}
}

static void	free_page(void *page_start)
{
	int	i;

	i = 0;
	while (i < LARGE)
	{
		if (g_segments.avail_segs[i])
			remove_dangling(&(g_segments.avail_segs[i]), page_start);
		i++;
	}
}

static void *page_check(void *page)
{
	void	*ptr;
	size_t	pagesize;

	ptr = ((t_info *)page)->page_start;
	pagesize = guess_pagesize(((t_header *)page)->index);
	while (ptr < ((t_info *)page)->page_start + pagesize)
	{
		if (((t_header *)ptr)->used)
			return (NULL);
		if (((t_header *)ptr)->len == 0)
			break ;
		ptr = ptr + sizeof(t_header) + ((t_header *)ptr)->len;
	}
	((t_info *)page)->pageid = (void *)-1;
	free_page(((t_info *)page)->page_start);
	munmap(((t_info *)page)->page_start, pagesize);
	return (NULL);
}

static void *cleanup(void __attribute__((unused)) *arg)
{
	size_t	i;
	void	*seg;
	t_info	thread_info;

	while (1)
	{
		printf("Sleeping\n");
		sleep(CLEAN_INTERVAL);
		i = 0;
		while (i < LARGE)
		{
			if ((seg = g_segments.avail_segs[i]))
			{
				thread_info.page_start = ((t_header *)seg)->page_start;
				thread_info.pageid = pageid[((t_header *)seg)->pageid];
				if (pthread_create(&(pageid[((t_header *)seg)->pageid]), NULL, page_check, &thread_info))
					break ;
				pthread_join(pageid[((t_header *)seg)->pageid], NULL);
				thread_info.pageid = NULL;
			}
			i++;
		}
	}
	printf("Got in here.\n");
	return (NULL);
}

void	free(void *ptr)
{
	static int	i = 0;
	pthread_t	thread;
	t_header 	*seg;

	if (!ptr)
		return ;
	if (i == 0)
	{
		printf("Creating thread.\n");
		if (pthread_create(&thread, NULL, cleanup, NULL))
		{
			printf("Failed to create pthread %s\n", strerror(errno));
			i = 0;
		}
		else
			i++;
	}
	seg = ((t_header *)(ptr - sizeof(t_header)));
	if (!valid_chksum(seg))
		return ;
	if (seg->index == LARGE_IND)
	{
		munmap(seg, seg->len);
		return ;
	}
	seg->used = 0;
	bzero(ptr, seg->len);
	seg->next = g_segments.avail_segs[seg->len];
	g_segments.avail_segs[seg->len] = seg;
}