/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liladam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 02:37:43 by asyed             #+#    #+#             */
/*   Updated: 2018/03/17 05:09:15 by asyed            ###   ########.fr       */
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
		addr = malloc(100);
		free(addr);
		i++;
	// }
	return (0);
}
