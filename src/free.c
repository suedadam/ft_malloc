/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/15 17:55:09 by asyed             #+#    #+#             */
/*   Updated: 2018/03/15 18:41:25 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void 	free(void *ptr)
{
	t_header *l_ptr;

	l_ptr = ptr - sizeof(t_header);
	if (l_ptr->large)
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
}
