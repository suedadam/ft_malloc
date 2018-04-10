/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 17:17:50 by asyed             #+#    #+#             */
/*   Updated: 2018/04/09 19:34:19 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*adam_realloc(void *ptr, size_t size)
{
	void	*new;

	if (!ptr || !valid_chksum(ptr - sizeof(t_header)))
		return (adam_malloc(size));
	if (((t_header *)(ptr - sizeof(t_header)))->len > size)
	{
		if ((new = g_segments.avail_segs[size]))
		{
			g_segments.avail_segs[size] = ((t_header *)new)->next;
			((t_header *)new)->used = 1;
		}
		else
		{
			if (!(new = adam_malloc(size)))
				return (NULL);
			new = new - sizeof(t_header);
		}
		ft_memcpy(new + sizeof(t_header), ptr,
				((t_header *)(ptr - sizeof(t_header)))->len);
		adam_free(ptr);
		return (new + sizeof(t_header));		
	}
	return (ptr);
}