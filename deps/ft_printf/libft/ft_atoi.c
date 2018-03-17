/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 11:43:05 by asyed             #+#    #+#             */
/*   Updated: 2017/09/24 20:28:41 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int			sign;
	long long	res;

	res = 0;
	while (ft_isspace(*nptr))
		nptr++;
	if (*nptr == '-' && (sign = -1))
		nptr++;
	else if ((sign = 1) && *nptr == '+' && (nptr++))
		;
	if (!ft_isdigit(*nptr))
		return (0);
	while (*nptr)
	{
		if (!ft_isdigit(*nptr) && (nptr++))
			break ;
		if ((*nptr - '0') > 9)
			break ;
		res = (10 * res) + (*nptr - '0');
		if (res < 0)
			return (0);
		nptr++;
	}
	return (int)(res * sign);
}
