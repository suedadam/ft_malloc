/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liltest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 02:37:43 by asyed             #+#    #+#             */
/*   Updated: 2018/03/19 12:44:24 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdlib.h>
// #include "ft_malloc.h"

int	main(void)
{
	int		i,x, size, test2;
	char	*addr[1025];

	srand(time(NULL));
	i = 0;
	while (i < 1024)
	{
		size = rand() % 10240;
		printf("Allocating %d\n", size);
		addr[i] = malloc(size);
		x = 0;
		while (x < size)
		{
			addr[i][x] = 'A';
			x++;
		}
		if (size % 2)
		{
			if (rand()%2)
			{
				test2 = 0;
				while (test2 <= size)
					test2 = rand() % 10241;
				addr[i] = realloc(addr[i], test2);
				x = 0;
				while (x < size)
				{
					addr[i][x] = 'A';
					x++;
				}
			}
			else
				free(addr[i]);
		}
		i++;
	}
	return (0);
}
