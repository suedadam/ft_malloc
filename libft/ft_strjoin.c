/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 22:33:13 by asyed             #+#    #+#             */
/*   Updated: 2017/09/21 22:36:46 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	srclen;
	size_t	dstlen;

	new = NULL;
	if (s1 && s2)
	{
		srclen = ft_strlen(s1);
		dstlen = ft_strlen(s2);
		new = (char *)malloc((srclen + dstlen + 1) * sizeof(char));
		if (!new)
			return (NULL);
		ft_bzero(new, srclen + dstlen + 1);
		new = ft_strcat(new, s1);
		ft_strcat(&new[srclen], s2);
	}
	return (new);
}
