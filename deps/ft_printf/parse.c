/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/14 00:55:06 by asyed             #+#    #+#             */
/*   Updated: 2017/11/27 15:52:08 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	parse_options(char **str, t_options *info, va_list ap)
{
	int	i;

	while (IS_FLAG(**str))
	{
		i = 0;
		while (flags[i].command)
		{
			if (**str == flags[i].command)
			{
				flags[i].func(info);
				break ;
			}
			i++;
		}
		(*str)++;
	}
	min_width(str, info, ap);
	precision(str, info, ap);
	l_modifier(str, info, ap);
}

void	min_width(char **str, t_options *info, va_list ap)
{
	if (**str == '*')
	{
		info->min_width += va_arg(ap, int);
		(*str)++;
	}
	else if (**str >= '0' && **str <= '9')
	{
		info->min_width += ft_atoi(*str);
		(*str) += s_n_length(info->min_width);
	}
}

void	precision(char **str, t_options *info, va_list ap)
{
	if (**str == '.')
	{
		(*str)++;
		if (**str == '*')
		{
			info->precision = va_arg(ap, int);
			(*str)++;
		}
		else if (**str >= '0' && **str <= '9')
		{
			info->precision = ft_atoi(*str);
			(*str) += s_n_length(info->precision);
		}
		info->altform = 0;
	}
}

/*
** The length modifier - This is a straight copy from my old code
** Shorten/Norm this bullshit
*/

void	setitter(char **str, t_options *info, int num)
{
	info->length = num;
	(*str)++;
}

void	l_modifier(char **str, t_options *info, va_list ap)
{
	while (IS_LMOD(**str))
	{
		if (**str == 'h')
		{
			(*str)++;
			if (**str == 'h')
				setitter(str, info, 2);
			else
				info->length = 1;
		}
		else if (**str == 'l')
		{
			(*str)++;
			if (**str == 'l')
				setitter(str, info, 4);
			else
				info->length = 3;
		}
		else if (**str == 'j')
			setitter(str, info, 5);
		else if (**str == 'z')
			setitter(str, info, 6);
	}
	(void)ap;
}
