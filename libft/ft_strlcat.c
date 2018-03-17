/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 11:43:05 by asyed             #+#    #+#             */
/*   Updated: 2017/09/25 12:46:06 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	slen;
	size_t	dlen;

	i = 0;
	slen = ft_strlen(src);
	dlen = ft_strlen(dest);
	if (dlen >= n)
		return (n + slen);
	i += dlen;
	dest = &dest[dlen];
	while (*src && i < (n - 1))
	{
		*dest++ = *src++;
		i++;
	}
	*dest = '\0';
	return (slen + dlen);
}
