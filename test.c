/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 00:16:14 by asyed             #+#    #+#             */
/*   Updated: 2018/03/18 03:55:26 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

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

void	validate(char **test, int total, size_t size, size_t size2)
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
	while (i < 30000)
	{
		printf("[%d]", i);
		if (i % 2)
		{
			if (!(test[i] = malloc(sizeof(char) * 1028)))
			{
				printf("Fail bitch\n");
				exit(-2);
			}
			test_copy(test[i], 1024, i + 'A');
		}
		else
		{
			if (!(test[i] = malloc(sizeof(char) * 120)))
			{
				printf("Fail bitch\n");
				exit(-2);
			}
			test_copy(test[i], 119, i + 'A');
		}
		printf("Returned %p\n", test[i]);
		validate(test, i, 120, 1028);
		// test[i] = realloc(test[i], 128);
		// printf("Test [%d] = %p\n", i, test[i]);
		// validate(test, i, 128, 120);
		i++;
	}
	exit(42);
}
