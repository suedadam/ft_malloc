/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 00:05:42 by asyed             #+#    #+#             */
/*   Updated: 2017/09/23 00:45:54 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putcstr(char const *s, int fd, int max)
{
	int	i;

	i = 0;
	if (s)
		while (s[i] && i < max)
			write(fd, &(s[i++]), 1);
}
