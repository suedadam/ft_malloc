/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/27 15:40:46 by asyed             #+#    #+#             */
/*   Updated: 2017/11/27 15:46:06 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		wcharstr(va_list ap, t_options *info)
{
	wchar_t *str;
	char	buf[1024];
	int		i;

	ft_bzero(buf, 1024);
	str = (wchar_t *)va_arg(ap, wchar_t *);
	if (!str)
		write(1, "(null", 6);
	i = ft_wcslen(str);
	if (!info->precision)
		info->precision = i;
	if (i < info->min_width)
		ft_memset(buf, ' ', info->min_width - info->precision);
	if (!info->left)
		print_buffer(buf, info);
	ft_putwstr(str);
	info->written += info->precision;
	if (info->left)
		print_buffer(buf, info);
	return (1);
}

int		string(va_list ap, uint8_t caps, t_options *info)
{
	char	*str;
	char	buf[1024];
	int		i;

	ft_bzero(buf, 1024);
	caps = (info->length == 3) ? 1 : caps;
	if (caps)
		return (wcharstr(ap, info));
	str = va_arg(ap, char *);
	if (!str)
		write(1, "(null)", 6);
	i = ft_strlen(str);
	if (!info->precision)
		info->precision = i;
	if (i < info->min_width)
		ft_memset(buf, ' ', info->min_width - info->precision);
	if (!info->left)
		print_buffer(buf, info);
	write(1, str, info->precision);
	info->written += info->precision;
	if (info->left)
		print_buffer(buf, info);
	return (1);
}
