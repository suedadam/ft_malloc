/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:55:09 by asyed             #+#    #+#             */
/*   Updated: 2018/03/17 03:42:50 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	free(void *ptr)
{
	static int	clean_up = 0;
	t_header	*l_ptr;

	if (!ptr)
		return ;
	l_ptr = ptr - sizeof(t_header);
	if (!valid_chksum(l_ptr))
	{
		printf("Invalid chksum\n");
		exit(23);
		return ;
	}
	pthread_mutex_lock(&(g_mutex[l_ptr->index]));
	l_ptr->used = 0;
	bzero(ptr, l_ptr->len);
	pthread_mutex_unlock(&(g_mutex[l_ptr->index]));
	if (clean_up++ == CLEAN_INTERVAL)
		;
	// 	cleaning_lady(&clean_up, 0);
}
