/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:37:08 by asyed             #+#    #+#             */
/*   Updated: 2018/03/16 21:18:10 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

void			*g_pages[3] = {NULL, NULL, NULL};
pthread_mutex_t	g_mutex[3] = {
	PTHREAD_MUTEX_INITIALIZER,
	PTHREAD_MUTEX_INITIALIZER,
	PTHREAD_MUTEX_INITIALIZER
};

void	*init_page(size_t pagesize)
{
	void	*tmp;

	printf("Allocated new page\n");
	if ((tmp = mmap(NULL, pagesize, PROT_ALL, FT_MAP_ANON, -1, 0)) == MAP_FAILED)
		return (NULL);
#ifdef FT_UNDEFINED
	bzero(tmp, pagesize);
#endif	
	return (tmp);
}

static int	next_page(t_header **l_page, void **curr_page, size_t pagesize)
{
	void	*tmp;

	if (!(tmp = init_page(pagesize)))
		return (-1);
	(*l_page)->next_page = tmp;
	*curr_page = tmp;
	(*l_page) = (t_header *)*curr_page;
	return (0);
}

/*
** 0 on failure
** non-0 on success.
*/

static int	finite_block(void **curr_page, t_header **l_page, size_t req_len, size_t pagesize)
{
	//Fits
	if ((*l_page)->len >= req_len)
	{
		(*l_page)->used = 1;
		return (req_len);
	}
	else if ((*l_page)->next_page)
	{
		*curr_page = (*l_page)->next_page;
		*l_page = (t_header *)(*curr_page);
	}
	else if ((((void *)(*l_page)) + (*l_page)->len) < (*curr_page + pagesize))
		*l_page = ((void *)(*l_page)) + (*l_page)->len;
	else
	{
		printf("Finite block!!!!\n");
		next_page(l_page, curr_page, pagesize);
	}
	return (0);
}

static int	infinite_block(void **curr_page, t_header **l_page, size_t req_len, size_t pagesize)
{
	void	*void_page;

	void_page = ((void *)(*l_page)) + sizeof(t_header);
	if ((void_page + req_len) <= (*curr_page + pagesize))
	{
		(*l_page)->used = 1;
		(*l_page)->len = req_len;
		void_page = *l_page;
		if (void_page + req_len + sizeof(t_header) <= (*curr_page + pagesize))
		{
			((t_header *)(((void *)(*l_page)) + (*l_page)->len))->next_page = (*l_page)->next_page;
			(*l_page)->next_page = NULL;
		}
		return (0);
	}
	else if ((*l_page)->next_page)
	{
		*curr_page = (*l_page)->next_page;
		*l_page = (t_header *)(*curr_page);
		return (1);
	}
	next_page(l_page, curr_page, pagesize);
	return (1);
}

void		*find_space(void *curr_page, size_t pagesize, size_t req_len)
{
	t_header	*l_page;
	void		*ret;

	l_page = (t_header *)curr_page;
	while ((void *)l_page < (curr_page + pagesize))
	{
		if (!l_page->used)
		{
			l_page->page_start = curr_page;
			if (!l_page->len)
			{
				if (infinite_block(&curr_page, &l_page, req_len, pagesize))
					continue ;
			}
			else
			{
				if (!finite_block(&curr_page, &l_page, req_len, pagesize))
					continue ;
			}
			return ((void *)l_page + sizeof(t_header)); 
		}
		if (l_page->next_page)
		{
			curr_page = l_page->next_page;
			l_page = (t_header *)curr_page;
			continue ;
		}
		else if ((void *)l_page + l_page->len + sizeof(t_header) >= (curr_page + pagesize))
		{
			next_page(&l_page, &curr_page, pagesize);
			continue ;
		}
		l_page = (void *)l_page + l_page->len + sizeof(t_header);
	}
	printf(" Should've never gotten here.\n");
	exit(21);
	return (NULL);
}

void 		*malloc(size_t size)
{
	if (size == 0)
		size = 1;
	if (size <= TINY)
		return (size_spacer(TINY_IND, PAGESIZE(TINY), size));
	if (size > TINY && size < LARGE)
		return (size_spacer(SMALL_IND, PAGESIZE(LARGE), size));
	return (size_spacer(LARGE_IND, size + sizeof(t_header), size));
}

void	test_copy(char *test, int total, char c)
{
	for (int i = 0; i < total; ++i)
	{
		test[i] = c;
	}
}

void	matches(char *test, char c)
{
	for (int i = 0; i < 49; ++i)
	{
		if (test[i] != c)
		{
			printf("FAILEDDDDD\n");
			printf("Line = \"%s\"\n", test);
			exit(1);
		}
	}
}

void	validate(char **test, int total, int size, int size2)
{
	t_header *head;
	for (int i = 0; i < total; ++i)
	{
		if (test[i])
		{

			head = (void *)test[i] - sizeof(t_header);
			if (head->len != size && head->len != size2)
			{
				printf("Failed %zu\n", head->len);
				exit(20);
			}
			matches(test[i], i + 'A');
		}
		else
		{
			printf("Randomly free'd? :D\n");
		}
	}
}

int		main(void)
{
	char	*test[30001];
	int		i;

	i = 0;
	while (i < 300)
	{
		printf("[%d]", i);
		if (!(test[i] = malloc(sizeof(char) * 120)))
		{
			printf("Fail bitch\n");
			exit(-2);
		}
		printf("Returned %p\n", test[i]);
		test_copy(test[i], 119, i + 'A');
		validate(test, i, 120, 128);
		test[i] = realloc(test[i], 128);
		printf("Test[%d] = %p\n", i, test[i]);
		validate(test, i, 128, 120);
		i++;
	}
	exit(42);
}