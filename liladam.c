/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liladam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 02:37:43 by asyed             #+#    #+#             */
/*   Updated: 2018/03/17 14:11:52 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "ft_malloc.h"

int	main(void)
{
	int		i;
	char	*addr;

	i = 0;
	// while (i < 1024)
	// {
		printf("[%d]\n", i);
		addr = malloc(350404);
		free(addr);
		show_alloc_mem();
		i++;
	// }
	return (0);
}
