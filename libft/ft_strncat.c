/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:34:03 by asyed             #+#    #+#             */
/*   Updated: 2017/09/23 00:35:55 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *dest, const char *src, size_t n)
{
	void	*r;

	r = dest;
	if (n)
	{
		while (*dest != '\0')
			dest++;
		while (n--)
		{
			if ((*dest = *src++) == 0)
				break ;
			dest++;
		}
		*dest = '\0';
	}
	return (r);
}
