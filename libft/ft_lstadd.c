/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 11:33:55 by asyed             #+#    #+#             */
/*   Updated: 2017/09/23 01:06:29 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstadd(t_list **alst, t_list *new)
{
	t_list	*save;

	save = (*alst);
	*alst = new;
	if (save)
	{
		(*save).next = (*alst)->next;
		(*alst)->next = save;
	}
}
