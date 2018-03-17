/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:38:10 by asyed             #+#    #+#             */
/*   Updated: 2017/09/23 00:49:40 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*new;

	i = 0;
	new = NULL;
	if (s && f)
	{
		new = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
		if (!new)
			return (NULL);
		ft_bzero(new, ft_strlen(s) + 1);
		while (s[i])
		{
			new[i] = f(i, s[i]);
			i++;
		}
		new[i] = '\0';
	}
	return (new);
}
