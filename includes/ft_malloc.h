/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 13:33:19 by asyed             #+#    #+#             */
/*   Updated: 2018/03/16 19:26:04 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <sys/mman.h>
# include <pthread.h>
# include <string.h>

# define TINY_IND 0
# define SMALL_IND 1
# define LARGE_IND 2
# define TINY 128
# define LARGE 1024
# define PAGESIZE(x) ((x + sizeof(t_header)) * 100)
# define PROT_ALL (PROT_READ | PROT_WRITE | PROT_EXEC)
# define FT_MAP_ANON (MAP_ANONYMOUS | MAP_PRIVATE)

typedef struct __attribute__((packed)) s_header
{
	size_t		len;
	uint8_t		used:1;
	uint8_t		index:2;
	void		*page_start;
	void		*next_page;
}				t_header;

void 	free(void *ptr);
void 	*malloc(size_t size);
void 	*realloc(void *ptr, size_t size);
void	*size_spacer(int page_index, size_t pagesize, size_t size);
void	*large_alloc(size_t size);
void	*find_space(void *curr_page, size_t pagesize, size_t req_len);
int		get_memseg_size(uint8_t index);
void	*init_page(size_t pagesize);

/*
** http://pubs.opengroup.org/onlinepubs/009695399/functions/pthread_mutex_lock.html
** http://man7.org/linux/man-pages/man2/mmap.2.html
*/

extern void				*g_pages[3];
extern pthread_mutex_t	g_mutex[3];
// pthread_mutex_t	g_mutex[3] = {PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER};

#endif