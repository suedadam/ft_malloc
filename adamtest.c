/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adamtest.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/09 13:49:46 by asyed             #+#    #+#             */
/*   Updated: 2018/04/09 16:24:47 by asyed            ###   ########.fr       */
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
		if (!(ret = adam_malloc(2)))
		{
			printf("Failed :%d\n", i);
			return (EXIT_FAILURE);
		}
		adam_free(ret);
		printf("%d ok %p\n", i, ret);
		i++;
	}
	// adam_malloc(1024);
}