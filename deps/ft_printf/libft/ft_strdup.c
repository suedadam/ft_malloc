/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 15:07:21 by asyed             #+#    #+#             */
/*   Updated: 2017/09/23 00:09:40 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *s)
{
	char	*dest;
	int		i;

	dest = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (dest)
	{
		i = 0;
		while (*s)
			dest[i++] = *s++;
		dest[i] = '\0';
		return (dest);
	}
	return (NULL);
}
