/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chksum.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/19 16:12:55 by asyed             #+#    #+#             */
/*   Updated: 2018/03/19 16:13:03 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int			valid_chksum(void *l_ptr)
{
	uint8_t		sum;
	size_t		i;
	void		*increment;
	t_header	copy;

	sum = 0;
	i = 0;
	if (!non_allocated(l_ptr, 0))
		return (0);
	ft_memcpy(&copy, l_ptr, sizeof(t_header));
	copy.chksum = 0;
	increment = &copy;
	while (i++ < sizeof(t_header))
	{
		sum += *(unsigned char *)increment;
		increment++;
	}
	return (sum == ((t_header *)l_ptr)->chksum);
}
