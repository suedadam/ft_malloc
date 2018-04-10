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

inline __attribute__((always_inline)) int		kill_cleaner(uint16_t id)
{
	if (pageid[id])
	{
		if (pageid[id] == (void *)-1)
			return (EXIT_FAILURE);
		pthread_cancel(pageid[id]);
		pageid[id] = NULL;
	}
	return (EXIT_SUCCESS);
}

/*
** Align to uint64_t to reduce itterations.
*/

inline __attribute__((always_inline)) uint8_t	chksum(void *mem)
{
	uint8_t		sum;
	size_t		i;

	((t_header *)mem)->chksum = 0;
	sum = *(uint32_t *)mem;
	mem += sizeof(uint32_t);
	i = sizeof(uint32_t);
	while ((i += sizeof(uint64_t)) < sizeof(t_header))
	{
		sum += *(uint64_t *)mem;
		mem += sizeof(uint64_t);
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
	i = sizeof(uint32_t);
	sum = *(uint32_t *)inc;
	inc += sizeof(uint32_t);
	while ((i += sizeof(uint64_t)) < sizeof(t_header))
	{
		sum += *(uint64_t *)inc;
		inc += sizeof(uint64_t);
	}
	return (sum == ((t_header *)ptr)->chksum);
}