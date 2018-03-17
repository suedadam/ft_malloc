/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 22:22:48 by asyed             #+#    #+#             */
/*   Updated: 2017/11/27 15:28:41 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

struct s_flag_entry	flags[] = {
	{'#', &altform},
	{'0', &padded},
	{'-', &left},
	{' ', &space},
	{'^', &special},
	{'+', &plus}
};

struct s_entry		conversion[] = {
	{'s', &string},
	{'d', &integer},
	{'%', &percent},
	{'u', &uinteger},
	{'c', &charparse},
	{'x', &hexadec},
	{'p', &pointeraddr},
	{'i', &integer},
	{'o', &octal},
};

void	command_search(const char **str, va_list ap, t_options *info)
{
	int	i;

	i = 0;
	while (conversion[i].command)
	{
		if (ft_tolower(**str) == conversion[i].command)
		{
			*str += conversion[i].func(ap, CAPS(**str), info);
			return ;
		}
		i++;
	}
}

int		ft_printf(const char *str, ...)
{
	va_list		ap;
	t_options	info;
	char		buffer[1024];

	va_start(ap, str);
	info.written = 0;
	bzero(buffer, 1024);
	while (*str)
	{
		if (*str == '%')
		{
			if (*buffer)
				print_buffer(buffer, &info);
			clearvar(&info);
			str++;
			parse_options((char **)&str, &info, ap);
			command_search(&str, ap, &info);
		}
		else
			addchar(buffer, *str++);
	}
	if (*buffer)
		print_buffer(buffer, &info);
	va_end(ap);
	return (info.written);
}
