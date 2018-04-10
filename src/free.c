/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 16:19:12 by asyed             #+#    #+#             */
/*   Updated: 2018/04/09 19:43:23 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	adam_free(void *ptr)
{
	t_header *seg;

	seg = ((t_header *)(ptr - sizeof(t_header)));
	seg->used = 0;
	bzero(ptr, seg->len);
	seg->next = g_segments.avail_segs[seg->len];
	g_segments.avail_segs[seg->len] = seg;
}