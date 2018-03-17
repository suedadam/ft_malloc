/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:02:04 by asyed             #+#    #+#             */
/*   Updated: 2017/09/23 00:08:21 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	if (n)
		while (n--)
		{
			if (*(unsigned char *)s++ == (unsigned char)c)
				return ((void *)(s - 1));
		}
	return (NULL);
}
