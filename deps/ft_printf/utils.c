/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 00:38:23 by asyed             #+#    #+#             */
/*   Updated: 2017/11/27 15:23:53 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Excuse info->written so that we can use it throughout the whole itteration
** of the input.
*/

void	clearvar(t_options *info)
{
	info->altform = 0;
	info->padding = 0;
	info->neg = 0;
	info->space = 0;
	info->sign = 0;
	info->left = 0;
	info->plus = 0;
	info->min_width = 0;
	info->precision = 0;
	info->length = 0;
	info->buf = NULL;
	info->precisionbuf = NULL;
}

size_t	s_n_length(intmax_t n)
{
	int	i;

	i = 0;
	if (!n)
		return (1);
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

size_t	u_n_length(uintmax_t n)
{
	int	i;

	i = 0;
	if (!n)
		return (1);
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*numbase(size_t dec, int base, uint8_t caps, int *i)
{
	static	char	buffer[40];

	if (!*i)
		ft_bzero(buffer, 40);
	if (!dec)
		return (NULL);
	numbase(dec / base, base, caps, i);
	if (caps)
		buffer[*i] = "0123456789ABCDEF"[dec % base];
	else
		buffer[*i] = "0123456789abcdef"[dec % base];
	(*i)++;
	return (buffer);
}

int		ft_unichar(va_list ap, t_options *info)
{
	int c;

	c = va_arg(ap, wchar_t);
	if (c < 0x80)
		ft_putchar(c);
	else if (c < 0x800)
	{
		ft_putchar(0xC0 | (c >> 6));
		ft_putchar(0x80 | (c & 0x3F));
	}
	else if (c < 0x10000)
	{
		ft_putchar(0xE0 | (c >> 12));
		ft_putchar(0x80 | (c >> 6 & 0x3F));
		ft_putchar(0x80 | (c & 0x3F));
	}
	else if (c < 0x200000)
	{
		ft_putchar(0xF0 | (c >> 18));
		ft_putchar(0x80 | (c >> 12 & 0x3F));
		ft_putchar(0x80 | (c >> 6 & 0x3F));
		ft_putchar(0x80 | (c & 0x3F));
	}
	(void)info;
	return (1);
}
