/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liladam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 14:11:52 by asyed             #+#    #+#             */
/*   Updated: 2018/04/09 20:00:32 by asyed            ###   ########.fr       */
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
			printf("FAILEDDDDD %d %p\n", i, test);
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
		// else
		// {
		// 	printf("Randomly free'd? :D\n");
		// }
	}
}

int	pow2(int i)
{
	while ((!(i % 2)) && i > 1)
		i /= 2;
	return (i == 1);
}

int		main(void)
{
	char	*test[30001];
	int		i;

	i = 0;
	while (i < 3001)
	{
		printf("[%d]", i);
		if (!(test[i] = malloc(sizeof(char) * 120)))
		{
			printf("Fail bitch\n");
			exit(-2);
		}
		test_copy(test[i], 119, i + 'A');
		validate(test, i, 120, 128);
		if (pow2(i))
		{
			free(test[i]);
			test[i] = NULL;
		}
		else
			test[i] = realloc(test[i], 128);
		printf("New = %p\n", test[i]);
		// printf("Test [%d] = %p\n", i, test[i]);
		i++;
	}
	exit(42);
}