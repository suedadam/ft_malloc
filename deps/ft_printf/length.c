/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 15:34:36 by asyed             #+#    #+#             */
/*   Updated: 2017/11/27 15:39:28 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		build_precision(t_options *info)
{
	int			i;
	static char buf[1024] = "";

	i = 0;
	ft_bzero(buf, 1024);
	while (i < info->precision)
	{
		buf[i] = '0';
		i++;
	}
	info->precisionbuf = buf;
	return (1);
}

int		build_minwidth(t_options *info, intmax_t numlen)
{
	int			i;
	static char buf[1024];

	i = 0;
	ft_bzero(buf, 1024);
	while (i < info->min_width)
	{
		buf[i] = (info->padding) ? '0' : ' ';
		i++;
	}
	if ((info->min_width + info->precision) < numlen && info->space)
		buf[i] = ' ';
	info->buf = buf;
	return (1);
}

int		precision_adjust(t_options *info, intmax_t num)
{
	intmax_t	length;

	length = s_n_length(num);
	if (info->precision)
	{
		info->padding = 0;
		if (info->precision > length)
		{
			info->precision -= length;
			info->min_width -= info->precision;
		}
		else
			info->precision = 0;
	}
	if (info->min_width)
	{
		info->min_width -= length + info->plus;
		if (info->min_width < 0)
			info->min_width = (info->space) ? 1 : 0;
	}
	if (num < 0)
		info->space = 0;
	build_precision(info);
	build_minwidth(info, length);
	return (1);
}

int		u_precision_adjust(t_options *info, uintmax_t num)
{
	uintmax_t	length;

	length = u_n_length(num);
	if (info->precision)
	{
		info->padding = 0;
		if ((uintmax_t)info->precision > length)
		{
			info->precision -= length;
			info->min_width -= info->precision;
		}
		else
			info->precision = 0;
	}
	if (info->min_width)
	{
		info->min_width -= length + info->plus;
		if (info->min_width < 0)
			info->min_width = (info->space) ? 1 : 0;
	}
	build_precision(info);
	build_minwidth(info, length);
	return (1);
}

void	alignment_handle(t_options *info, char sign, intmax_t num)
{
	if (info->left)
	{
		(sign) ? ft_putchar(sign) : 0;
		print_buffer(info->precisionbuf, info);
		ft_putnbr(num);
		print_buffer(info->buf, info);
	}
	else
	{
		if (info->padding)
		{
			(sign) ? ft_putchar(sign) : 0;
			print_buffer(info->buf, info);
		}
		else
		{
			print_buffer(info->buf, info);
			(sign) ? ft_putchar(sign) : 0;
		}
		print_buffer(info->precisionbuf, info);
		ft_putnbr(num);
	}
}
