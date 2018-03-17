/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 15:41:34 by asyed             #+#    #+#             */
/*   Updated: 2017/11/27 15:43:13 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Max itterated size = 1024 bytes.
*/

void	multi_print(char c, int n)
{
	char	buf[1024];
	int		i;

	i = 0;
	while (i < n)
		buf[i++] = c;
	ft_putstr(buf);
}

void	null_hex(t_options *info)
{
	ft_putchar('0');
	info->written++;
}
