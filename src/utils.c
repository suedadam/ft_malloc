/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 00:14:58 by asyed             #+#    #+#             */
/*   Updated: 2018/03/17 03:42:58 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void	*init_page(size_t pagesize)
{
	void	*tmp;

	if ((tmp = mmap(NULL, pagesize, PROT_ALL, FT_MAP_ANON, -1, 0))
				== MAP_FAILED)
		return (NULL);
	return (tmp);
}

int		next_page(t_header **l_page, void **curr_page, size_t pagesize)
{
	void	*tmp;

	if (!(tmp = init_page(pagesize)))
		return (-1);
	(*l_page)->next_page = tmp;
	*curr_page = tmp;
	(*l_page) = (t_header *)*curr_page;
	return (0);
}

/*
** # define PAGESIZE(x) ((x + sizeof(t_header)) * MAX_PER_PAGE)
*/

int		align_pagesize(size_t x)
{
	static int	sys_size = 0;
	size_t	test;
	size_t	page;

	if (!sys_size)
		sys_size = getpagesize();
	page = PAGESIZE(x);
	test = page % sys_size;
	return (page + test);
}

int		valid_chksum(void *l_ptr)
{
	uint8_t		sum;
	size_t		i;
	void		*increment;
	t_header	copy;

	sum = 0;
	i = 0;
	memcpy(&copy, l_ptr, sizeof(t_header));
	copy.chksum = 0;
	increment = &copy;
	while (i++ < sizeof(t_header))
	{
		sum += *(unsigned char *)increment;
		increment++;
	}
	return (sum == ((t_header *)l_ptr)->chksum);
}
