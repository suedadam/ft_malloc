/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_fetch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/12 13:20:47 by asyed             #+#    #+#             */
/*   Updated: 2017/11/27 14:46:07 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

__uint64_t	u_numfetch(va_list ap, t_options *info)
{
	__uint64_t ret;

	if (info->length == 1)
		ret = (unsigned short int)va_arg(ap, unsigned int);
	else if (info->length == 2)
		ret = (unsigned char)va_arg(ap, unsigned int);
	else if (info->length == 3)
		ret = va_arg(ap, unsigned long int);
	else if (info->length == 4)
		ret = va_arg(ap, unsigned long long int);
	else if (info->length == 5)
		ret = va_arg(ap, uintmax_t);
	else if (info->length == 6)
		ret = va_arg(ap, size_t);
	else
		ret = va_arg(ap, unsigned int);
	return (ret);
}

int64_t		s_numfetch(va_list ap, t_options *info)
{
	int64_t ret;

	if (info->length == 1)
		ret = (short int)va_arg(ap, int);
	else if (info->length == 2)
		ret = (char)va_arg(ap, int);
	else if (info->length == 3)
		ret = va_arg(ap, long int);
	else if (info->length == 4)
		ret = va_arg(ap, long long int);
	else if (info->length == 5)
		ret = va_arg(ap, intmax_t);
	else if (info->length == 6)
		ret = va_arg(ap, ssize_t);
	else
		ret = va_arg(ap, int);
	return (ret);
}
