/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 12:57:53 by asyed             #+#    #+#             */
/*   Updated: 2017/11/27 15:42:53 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		percent(va_list ap, uint8_t caps, t_options *info)
{
	ft_putchar('%');
	info->written++;
	(void)caps;
	(void)ap;
	return (1);
}

int		charparse(va_list ap, uint8_t caps, t_options *info)
{
	ft_putchar((unsigned char)va_arg(ap, int));
	info->written++;
	(void)caps;
	return (1);
}

int		octal(va_list ap, uint8_t caps, t_options *info)
{
	uint64_t	hex;
	char		*save;
	int			i;

	i = 0;
	caps = (info->length == 3) ? 1 : caps;
	hex = u_numfetch(ap, info);
	save = numbase(hex, 8, caps, &i);
	i = ft_strlen(save);
	if (!i || !save)
		null_hex(info);
	info->written += (info->altform) ? 1 : 0;
	if (!info->left && info->altform && save && *save != '0')
		write(1, "0", 1);
	ft_putstr(save);
	info->written += i;
	if (info->left && info->altform && save && *save != '0')
		write(1, "0", 1);
	return (1);
}

int		hexadec(va_list ap, uint8_t caps, t_options *info)
{
	uint64_t	hex;
	char		buf[1024];
	char		*save;
	int			i;

	i = 0;
	ft_bzero(buf, 1024);
	hex = u_numfetch(ap, info);
	save = numbase(hex, 16, caps, &i);
	i = ft_strlen(save);
	if (!i)
		null_hex(info);
	if (info->altform)
	{
		addchar(buf, '0');
		addchar(buf, (caps) ? 'X' : 'x');
	}
	if (!info->left)
		print_buffer(buf, info);
	ft_putstr(save);
	info->written += i;
	if (info->left)
		print_buffer(buf, info);
	return (1);
}

int		pointeraddr(va_list ap, uint8_t caps, t_options *info)
{
	uint64_t	hex;
	char		*save;
	int			i;

	i = 0;
	if (!info->length)
		info->length = 4;
	hex = u_numfetch(ap, info);
	save = numbase(hex, 16, caps, &i);
	i = ft_strlen(save);
	if (!i)
	{
		ft_putstr("0x0");
		i += 3;
	}
	else
	{
		ft_putstr("0x");
		ft_putstr(save);
		i += 2;
	}
	info->written += i;
	return (1);
}
