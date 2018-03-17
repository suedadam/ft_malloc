/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/01 21:50:21 by asyed             #+#    #+#             */
/*   Updated: 2018/02/01 21:50:24 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int		storage_contains(char **overflow, char **line, int *count)
{
	int		i;
	char	*save;

	i = 0;
	while ((*overflow)[i])
		if ((*overflow)[i] == '\n')
		{
			save = ft_memalloc((ft_strlen(*overflow) - i) * SCHAR);
			if (!save)
				return (-1);
			save = ft_strcpy(save, &((*overflow)[i + 1]));
			*line = ft_strncpy(*line, *overflow, i);
			(*line)[i++] = '\0';
			free(*overflow);
			*overflow = save;
			return (1);
		}
		else
			i++;
	*count += i;
	*line = ft_strncpy(*line, *overflow, i);
	*line = (char *)ft_realloc_safe(*line, *count, *count + BUFF_SIZE + 1);
	free(*overflow);
	*overflow = NULL;
	return (0);
}

int		line_split(char **overflow, char **line, int *count)
{
	int	i;

	(*line)[*count] = '\0';
	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\n')
		{
			if ((*line)[i + 1])
			{
				*overflow = (char *)ft_memalloc((*count - i) * SCHAR);
				if (!*overflow)
					return (-1);
				*overflow = ft_strncpy(*overflow, (*line + i + 1), *count - i);
				(*overflow)[*count - i - 1] = '\0';
			}
			(*line)[i] = '\0';
			return (1);
		}
		i++;
	}
	return (0);
}

int		init(const int fd, char ***line, char ***overflow)
{
	if (fd < 0 || fd > 5000 || !*line || FDS <= 0 || BUFF_SIZE <= 0)
		return (-1);
	if (!*overflow)
	{
		if (!(*overflow = (char **)ft_memalloc(FDS * sizeof(char *))))
			return (-1);
	}
	if (!(**line = (char *)ft_memalloc((BUFF_SIZE + 1) * SCHAR)))
	{
		free(*overflow);
		return (-1);
	}
	return (0);
}

int		get_next_line(const int fd, char **line)
{
	static	char	**overflow;
	int				r;
	int				count;
	int				res;

	count = 0;
	if (init(fd, &line, &overflow))
		return (-1);
	if (overflow[fd] && (res = storage_contains(&(overflow[fd]), line, &count)))
		return (res);
	while ((r = read(fd, (*line + count), BUFF_SIZE)) > 0 && (count += r))
		if ((res = line_split(&(overflow[fd]), line, &count)))
			return (res);
		else if (r == BUFF_SIZE)
		{
			*line = (char *)ft_realloc_safe(*line, count * SCHAR,
					(count + BUFF_SIZE + 1) * SCHAR);
			if (!*line)
				return (-1);
		}
	if (r < 0 || ((*line)[count] = '\0'))
		return (-1);
	return (**line ? 1 : 0);
}
