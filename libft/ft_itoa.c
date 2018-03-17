/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 22:56:45 by asyed             #+#    #+#             */
/*   Updated: 2017/09/25 11:12:57 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static int		ft_getnumlength(int n)
{
	int	length;

	length = 0;
	if (n < 0)
	{
		length++;
		n = -n;
	}
	while (n)
	{
		n /= 10;
		length++;
	}
	return (length);
}

static	void	ft_itoa_helper(int n, char *new, int length)
{
	if (n < 0)
	{
		if (n < 0 && (n = -n))
			new[0] = '-';
		while (length > 0)
		{
			new[length--] = (n % 10) + '0';
			n /= 10;
		}
	}
	else
		while (length >= 0)
		{
			new[length--] = (n % 10) + '0';
			n /= 10;
		}
}

char			*ft_itoa(int n)
{
	char	*new;
	int		length;

	length = ft_getnumlength(n);
	new = (char *)malloc(((n ? length : 1) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	if (n)
	{
		if (n == -2147483648)
			return (ft_strcpy(new, "-2147483648"));
		new[length--] = '\0';
		ft_itoa_helper(n, new, length);
	}
	else
		ft_strcpy(new, "0");
	return (new);
}
