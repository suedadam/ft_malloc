/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:06:24 by asyed             #+#    #+#             */
/*   Updated: 2018/04/10 00:30:02 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

inline __attribute__((always_inline)) int		kill_cleaner(t_header *mem)
{
	if (pageid[mem->pageid])
	{
		if (pageid[mem->pageid] == (void *)-1)
			return (EXIT_FAILURE);
		pthread_cancel(pageid[mem->pageid]);
		pageid[mem->pageid] = NULL;
	}
	return (EXIT_SUCCESS);
}

inline __attribute__((always_inline)) uint8_t	chksum(void *mem)
{
	uint8_t		sum;
	size_t		i;

	sum = 0;
	i = 0;
	((t_header *)mem)->chksum = 0;
	while (i++ < sizeof(t_header))
	{
		sum += *(unsigned char *)mem;
		mem++;
	}
	return (sum);
}

inline __attribute__((always_inline)) int		index_calc(size_t size)
{
	if (size < TINY)
		return (TINY_IND);
	else if (size < LARGE)
		return (SMALL_IND);
	else
		return (LARGE_IND);
}

inline __attribute__((always_inline)) int		index2size(uint8_t index)
{
	if (index == 1)
		return (TINY);
	else
		return (LARGE);
}

inline __attribute__((always_inline)) int		valid_chksum(void *ptr)
{
	uint8_t		sum;
	size_t		i;
	t_header	copy;
	void		*inc;

	ft_memcpy(&copy, ptr, sizeof(t_header));
	copy.chksum = 0;
	inc = &copy;
	i = 0;
	sum = 0;
	while (i++ < sizeof(t_header))
	{
		sum += *(unsigned char *)inc;
		inc++;
	}
	return (sum == ((t_header *)ptr)->chksum);
}