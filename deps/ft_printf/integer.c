/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   integer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 15:42:29 by asyed             #+#    #+#             */
/*   Updated: 2017/11/27 15:42:32 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		uinteger(va_list ap, uint8_t caps, t_options *info)
{
	uintmax_t	num;

	info->length = (caps) ? 3 : info->length;
	num = u_numfetch(ap, info);
	u_precision_adjust(info, num);
	if (info->left)
	{
		print_buffer(info->precisionbuf, info);
		ft_uputnbr(num);
		print_buffer(info->buf, info);
	}
	else
	{
		print_buffer(info->buf, info);
		print_buffer(info->precisionbuf, info);
		ft_uputnbr(num);
	}
	info->written += u_n_length(num);
	return (1);
}

int		integer(va_list ap, uint8_t caps, t_options *info)
{
	intmax_t	num;
	char		sign;

	if (caps)
		num = va_arg(ap, long int);
	else
		num = s_numfetch(ap, info);
	precision_adjust(info, num);
	if (info->plus && num > 0)
		sign = '+';
	if (num < 0)
	{
		num = -num;
		sign = '-';
	}
	alignment_handle(info, sign, num);
	info->written += s_n_length(num) + IS_SET(sign);
	return (1);
}
