/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/21 22:37:53 by asyed             #+#    #+#             */
/*   Updated: 2017/09/23 01:43:54 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strtrim(char const *s)
{
	char	*new;
	char	*save;
	int		start;
	int		end;

	save = NULL;
	start = 0;
	if (!s)
		return (NULL);
	while (s[start] && TRIMSPACE(s[start]))
		start++;
	end = start + 1;
	while (s[end])
		end++;
	end--;
	while (s[end] && TRIMSPACE(s[end]))
		end--;
	new = (char *)malloc((end - start + 2) * sizeof(char));
	if (!new)
		return (NULL);
	save = new;
	while (start <= end)
		*new++ = s[start++];
	*new = '\0';
	return (save);
}
