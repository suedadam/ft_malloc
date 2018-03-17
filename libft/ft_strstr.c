/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 17:47:08 by asyed             #+#    #+#             */
/*   Updated: 2017/09/23 01:55:18 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strstr(const char *in, const char *str)
{
	char *begin;
	char *save;

	begin = (char *)in;
	save = (char *)str;
	if (!*save || in == str)
		return (begin);
	while (*in)
	{
		while (*in && *save && *in == *save)
		{
			in++;
			save++;
		}
		if (!(*save))
			return ((char *)in - ft_strlen(str));
		save = (char *)str;
		in = begin++;
	}
	return (NULL);
}
