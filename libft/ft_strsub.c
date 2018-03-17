/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 22:27:40 by asyed             #+#    #+#             */
/*   Updated: 2017/09/23 00:52:59 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	i = 0;
	new = NULL;
	if (s)
	{
		new = (char *)malloc((len + 1) * sizeof(char));
		if (!new)
			return (NULL);
		while (s[start + i] && i < len)
		{
			new[i] = s[start + i];
			i++;
		}
		new[i] = '\0';
	}
	return (new);
}
