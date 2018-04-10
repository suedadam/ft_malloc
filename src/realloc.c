/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:17:50 by asyed             #+#    #+#             */
/*   Updated: 2018/04/10 01:28:04 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*realloc(void *ptr, size_t size)
{
	void	*new;

	if (!ptr || !valid_chksum(ptr - sizeof(t_header)))
		return (malloc(size));
	if (((t_header *)(ptr - sizeof(t_header)))->len < size)
	{
		if (((t_header *)(ptr - sizeof(t_header *)))->index != 2 &&
			(new = g_segments.avail_segs[size]))
		{
			g_segments.avail_segs[size] = ((t_header *)new)->next;
			((t_header *)new)->used = 1;
		}
		else
		{
			if (!(new = malloc(size)))
				return (NULL);
			new = new - sizeof(t_header);
		}
		ft_memcpy(new + sizeof(t_header), ptr,
				((t_header *)(ptr - sizeof(t_header)))->len);
		free(ptr);
		return (new + sizeof(t_header));		
	}
	return (ptr);
}
