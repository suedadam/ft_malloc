/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 12:10:40 by asyed             #+#    #+#             */
/*   Updated: 2017/09/23 01:07:56 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*save;
	t_list	*new;

	if (!lst)
		return (NULL);
	new = (t_list *)malloc(sizeof(struct s_list));
	new = (*f)(lst);
	save = new;
	lst = lst->next;
	while (lst)
	{
		if (!(new->next = f(lst)))
		{
			free(new->next);
			new->next = NULL;
			return (save);
		}
		new = new->next;
		lst = lst->next;
	}
	return (save);
}
