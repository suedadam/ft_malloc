/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liltest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 02:37:43 by asyed             #+#    #+#             */
/*   Updated: 2018/03/18 01:24:23 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_malloc.h"

int	main(void)
{
	int		i;
	char	*addr;

	i = 0;
	addr = malloc(1024);
	printf("addr->len = %zu\n", ((t_header *)(addr - sizeof(t_header)))->len);
	free(addr);
	// while (i < 1024)
	// {
	// 	addr = malloc(1024);
	// 	addr[0] = 42;
	// 	free(addr);
	// 	i++;
	// }
	return (0);
}
