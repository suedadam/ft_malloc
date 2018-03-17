/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strccmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 11:13:00 by asyed             #+#    #+#             */
/*   Updated: 2018/01/31 23:15:54 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strccmp(const char *s1, const char *s2, char c)
{
	while (*s1 == *s2)
	{
		if (!*s1)
			return (0);
		if (*(s1 + 1) == c)
			break ;
		s1++;
		s2++;
	}
	return ((int)(*(unsigned char *)s1 - *(unsigned char *)s2));
}
