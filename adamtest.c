/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adamtest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 13:49:46 by asyed             #+#    #+#             */
/*   Updated: 2018/04/10 00:22:51 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

int	main(void)
{
	int		i;
	void	*ret;

	i = 0;
	while (i < 3)
	{
		if (!(ret = malloc(28)))
		{
			printf("Failed :%d\n", i);
			return (EXIT_FAILURE);
		}
		free(ret);
		printf("%d ok %p\n", i, ret);
		i++;
	}
	sleep(10);
	ret = malloc(28);
	printf("3 ok %p\n", ret);
	// free(ret);
	// while(1);
	// adam_malloc(1024);
}