/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/22 10:40:43 by asyed             #+#    #+#             */
/*   Updated: 2017/09/24 20:25:17 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*newlink;

	newlink = (t_list*)malloc(sizeof(t_list));
	if (!newlink)
		return (NULL);
	if (!content)
	{
		newlink->content = NULL;
		newlink->content_size = 0;
		return (newlink);
	}
	newlink->content = (void *)malloc(content_size * sizeof(void));
	if (!newlink->content)
		return (NULL);
	ft_bzero(newlink->content, content_size * sizeof(void));
	newlink->next = (void *)malloc(sizeof(struct s_list));
	ft_bzero(newlink->next, sizeof(struct s_list));
	newlink->content = ft_memcpy(newlink->content, content, content_size);
	newlink->content_size = content_size;
	newlink->next = NULL;
	return (newlink);
}
