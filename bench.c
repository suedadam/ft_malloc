#include <stdio.h>
#include <stdlib.h>

typedef struct __attribute__((packed))	s_header
{
	void		*page_start;
	void		*next;
	size_t		len;
	uint8_t		used:1;
	uint8_t		index:2;
	uint8_t		chksum;
	uint16_t	pageid;
}				t_header;


static __inline__ unsigned long long rdtsc(void)
{
  unsigned long long int x;
     __asm__ volatile (".byte 0x0f, 0x31" : "=A" (x));
     return x;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liladam.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 14:11:52 by asyed             #+#    #+#             */
/*   Updated: 2018/03/17 15:35:46 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ft_malloc.h"

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
	uint64_t	cycles;

	i = 0;
	cycles = rdtsc();
	while (i < 30000)
	{
		// printf("[%d]", i);
		if (!(test[i] = malloc(sizeof(char) * 1024)))
		{
			printf("Fail bitch\n");
			exit(-2);
		}
		// printf("Returned %p\n", test[i]);
		// test_copy(test[i], 119, i + 'A');
		// // validate(test, i, 120, 128);
		// test[i] = realloc(test[i], 128);
		// printf("Test [%d] = %p\n", i, test[i]);
		// // validate(test, i, 128, 120);
		// free(test[i]);
		// test[i] = NULL;
		i++;
	}
	printf("%llu\n", rdtsc() - cycles);
	while(1);
	exit(42);
}
