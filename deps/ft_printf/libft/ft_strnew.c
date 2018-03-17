/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 11:29:27 by asyed             #+#    #+#             */
/*   Updated: 2017/09/23 00:50:11 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strnew(size_t size)
{
	void	*var;
	int		i;

	i = 0;
	var = (void *)malloc(size + 1);
	if (var == 0)
		return ((char *)var);
	else
		ft_bzero(var, size + 1);
	return ((char *)var);
}
