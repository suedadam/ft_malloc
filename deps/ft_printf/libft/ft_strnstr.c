/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 17:47:08 by asyed             #+#    #+#             */
/*   Updated: 2017/09/24 19:49:41 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *in, const char *str, size_t n)
{
	char	*in_save;
	char	*str_save;
	size_t	n_save;

	if (!*str)
		return ((char *)in);
	in_save = (char *)in;
	str_save = (char *)str;
	n_save = n;
	while (n)
		if (*in == *str && *in++ && *str++ && n_save--)
			;
		else
		{
			if (!*str)
				return (in_save);
			in = ++in_save;
			if (!*in)
				return (NULL);
			n--;
			n_save = n;
			str = str_save;
		}
	return (NULL);
}
