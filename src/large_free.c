/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   large_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 14:15:49 by asyed             #+#    #+#             */
/*   Updated: 2018/03/17 14:16:41 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	update_prev(void *prev, void *next)
{
	if (!prev)
		g_pages[LARGE_IND] = next;
	else
		((t_header *)prev)->next_page = next;
}

void	cleanup_tty(void)
{
	void		**head;
	t_header	*l_page;
	void		*curr_page;
	void		*prev;

	pthread_mutex_lock(&(g_mutex[LARGE_IND]));
	head = &(g_pages[LARGE_IND]);
	if ((curr_page = *head))
	{
		prev = NULL;
		while (curr_page)
		{
			l_page = (t_header *)curr_page;
			if (!l_page->used)
				update_prev(prev, l_page->next_page);
			prev = curr_page;
			curr_page = l_page->next_page;
		}
	}
	pthread_mutex_unlock(&(g_mutex[LARGE_IND]));
}
