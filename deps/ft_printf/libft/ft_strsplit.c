/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 14:01:26 by asyed             #+#    #+#             */
/*   Updated: 2017/09/25 11:27:50 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_wordcount(char const *s, char c)
{
	int	words;

	words = 0;
	while (*s)
	{
		if (*s != c && (*(s + 1) == c || !*(s + 1)))
			words++;
		s++;
	}
	return (words);
}

static int	ft_mallocwords(char const *s, char c, char **array)
{
	int count;
	int i;

	i = 0;
	while (*s)
	{
		count = 0;
		while (*s && *s != c)
		{
			count++;
			s++;
		}
		if (count)
		{
			array[i] = (char *)malloc((count + 1) * sizeof(char));
			if (!array[i])
				return (0);
			ft_bzero(array[i++], (count + 1) * sizeof(char));
		}
		if (*s)
			s++;
		else
			break ;
	}
	return (i);
}

static	int	ft_strwrite(char const *s, char c, char **array, int words)
{
	int	i;
	int j;

	i = 0;
	while (i < words)
	{
		j = 0;
		while (*s)
		{
			if (*s != c)
				array[i][j++] = *s++;
			else if (*s == c)
			{
				while (*s && *(s + 1) && *s == c)
					s++;
				s--;
				break ;
			}
		}
		i++;
		s++;
	}
	return (1);
}

static	int	ft_freeall_test(char **array, char const *s, char c, int words)
{
	int	res;

	res = ft_mallocwords(s, c, array);
	if (res != words)
	{
		if (res)
			while (res)
				free(array[res--]);
		return (0);
	}
	return (1);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**array;
	int		words;

	if (s && c)
	{
		while (*s && *s == c)
			s++;
		words = ft_wordcount(s, c);
		array = (char **)malloc((words + 1) * sizeof(char *));
		if (!array)
			return (NULL);
		ft_bzero(array, (words + 1) * sizeof(char *));
		if (!ft_freeall_test(array, s, c, words))
			return (NULL);
		if (!ft_strwrite(s, c, array, words))
			return (NULL);
		return (array);
	}
	return (NULL);
}
