/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 19:06:24 by asyed             #+#    #+#             */
/*   Updated: 2018/04/09 19:27:01 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int	valid_chksum(void *ptr)
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