/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:37:08 by asyed             #+#    #+#             */
/*   Updated: 2018/03/16 00:09:17 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

static void	*init_page(size_t pagesize)
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
	void	*tmp;

	if ((*l_page)->len >= req_len)
	{
		(*l_page)->used = 1;
		return (req_len);
	}
	else if ((void *)(*l_page + (*l_page)->len) < (*curr_page + pagesize))
	{
		*l_page = (void *)*l_page + (*l_page)->len + sizeof(t_header);
		return (0);
	}
	else
	{
		if (next_page(l_page, curr_page, pagesize))
			return (0);
		return (req_len);
	}
}

static int	infinite_block(void **curr_page, t_header **l_page, size_t req_len, size_t pagesize)
{
	void	*void_page;

	void_page = (*l_page)->mem_seg;
	if ((void_page + req_len) < (*curr_page + pagesize))
	{
		(*l_page)->used = 1;
		(*l_page)->len = req_len;
		void_page = *l_page;
		((t_header *)(void_page + (*l_page)->len))->next_page = (*l_page)->next_page;
		(*l_page)->next_page = NULL;
		return (0);
	}
	else if ((*l_page)->next_page)
	{
		*curr_page = (*l_page)->next_page;
		*l_page = (t_header *)(*curr_page);
		return (-1);
	}
	else if (next_page(l_page, curr_page, pagesize))
		return (-2);
	return (-1);
}

void		*find_space(void *curr_page, size_t pagesize, size_t req_len)
{
	t_header	*l_page;
	void		*tmp;
	int			ret;

	l_page = (t_header *)curr_page;
	while ((void *)l_page < (curr_page + pagesize))
	{
		if (!(l_page->used))
		{
			if (l_page->next_page)
			{
				curr_page = l_page->next_page;
				l_page = (t_header *)curr_page;
				continue ;
			}
			l_page->mem_seg = (void *)l_page + sizeof(t_header);
			l_page->page_start = curr_page;
			if (!l_page->len)
			{
				if (!(ret = infinite_block(&curr_page, &l_page, req_len, pagesize)))
					return (l_page->mem_seg);
				else if (ret == -2)
					return (NULL);
			}
			else
			{
				if (!finite_block(&curr_page, &l_page, req_len, pagesize))
					return (l_page->mem_seg);
			}
		}
		else
			l_page = (void *)l_page + l_page->len + sizeof(t_header);
	}
	return (NULL);
}

void 		*malloc(size_t size)
{
	if (size <= TINY)
		return (size_spacer(0, PAGESIZE(TINY), size));
	if (size > TINY && size < LARGE)
		return (size_spacer(1, PAGESIZE(LARGE), size));
	return (large_alloc(size));
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
	for (int i = 0; i < 100; ++i)
	{
		if (test[i] != c)
		{
			printf("FAILEDDDDD\n");
			printf("Line = \"%s\"\n", test);
			exit(1);
		}
	}
}

void	validate(char **test, int total)
{
	for (int i = 0; i < total; ++i)
	{
		if (test[i])
		{
			matches(test[i], i + 'A');
			// printf("%s\n", test[i]);
		}
		else
		{
			printf("Randomly free'd? :D\n");
		}
	}
}

void 	*thread_func(void *arg)
{
	char	*test[151];
	int		i;

	i = 0;
	while (i < 150)
	{
		printf("[%d] ", i);
		if (!(test[i] = malloc(sizeof(char) * 101)))
		{
			printf("Fail bitch\n");
			exit(-2);
		}
		test_copy(test[i], 100, i + 'A');
		test[i] = realloc(test[i], 200);
		if (!(rand() % 84))
		{
			free(test[i]);
			test[i] = NULL;
		}
		validate(test, i);
		i++;
	}
	i = 149;
	while (i > 0)
	{
		free(test[i]);
		test[i] = NULL;
		i--;
	}
	return (NULL);
}

// int		main(void)
// {
// 	int i;
// 	int test;
// 	pthread_t thread[5];

// 	i = 0;
// 	srand(time(NULL));
// 	while (i < 5)
// 	{
// 		pthread_create(&(thread[0]), NULL, thread_func, (void *)&test);
// 		i++;
// 	}
// 	pthread_join(thread[0],NULL);
// 	pthread_join(thread[1],NULL);
// 	pthread_join(thread[2],NULL);
// 	pthread_join(thread[3],NULL);
// 	pthread_join(thread[4],NULL);
// 	exit(42);
// }
int		main(void)
{
	char	*test[150];
	int		i;

	i = 0;
	while (i < 150)
	{
		printf("[%d]\n", i);
		if (!(test[i] = malloc(sizeof(char) * 101)))
		{
			printf("Fail bitch\n");
			exit(-2);
		}
		test_copy(test[i], 100, i + 'A');
		test[i] = realloc(test[i], 200);
		validate(test, i);
		i++;
	}

	i = 149;
	while (i > 0)
	{
		free(test[i]);
		test[i] = NULL;
		i--;
	}
	exit(42);
}