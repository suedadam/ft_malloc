/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 12:35:36 by asyed             #+#    #+#             */
/*   Updated: 2017/09/23 00:08:05 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	if (n)
		while (n--)
		{
			if ((*(unsigned char *)dest++ =
				*(unsigned char *)src++) == (unsigned char)c)
				return (dest);
		}
	return (0);
}
