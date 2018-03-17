/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_safe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/19 12:16:25 by asyed             #+#    #+#             */
/*   Updated: 2018/02/01 21:51:02 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_realloc_safe(void *src, size_t old_size, size_t new_size)
{
	void	*new;

	if (!src)
		return (ft_memalloc(new_size));
	if (!new_size)
	{
		free(src);
		return (NULL);
	}
	new = (void *)ft_memalloc(new_size);
	if (!new)
		return (NULL);
	new = ft_memcpy(new, src, old_size);
	ft_bzero(new + old_size, new_size - old_size);
	free(src);
	return (new);
}