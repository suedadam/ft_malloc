/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 15:42:46 by asyed             #+#    #+#             */
/*   Updated: 2018/04/09 19:37:31 by asyed            ###   ########.fr       */
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
# include <unistd.h>
# include "libft/libft.h"
# include "ft_printf.h"

# define TINY_IND 0
# define SMALL_IND 1
# define LARGE_IND 2
# define CLEAN_INTERVAL 10
# define MAX_PER_PAGE 300
# define TINY 128
# define LARGE 2048
# define PAGESIZE(x) ((x + sizeof(t_header)) * MAX_PER_PAGE)
# define PROT_ALL (PROT_READ | PROT_WRITE | PROT_EXEC)
# define FT_MAP_ANON (MAP_ANONYMOUS | MAP_PRIVATE | MAP_NOCACHE)
# define OFFP_HEADER(x) ((void *)x + x->len + sizeof(t_header))

typedef struct __attribute__((packed))	s_header
{
	void		*page_start;
	void		*next;
	size_t		len;
	uint8_t		used:1;
	uint8_t		index:2;
	uint8_t		chksum;
}				t_header;

typedef struct	s_tree
{
	t_header	*avail_segs[LARGE];
}				t_tree;

int			valid_chksum(void *ptr);
void		adam_free(void *ptr);
void		*adam_malloc(size_t size);
void		*adam_realloc(void *ptr, size_t size);
size_t		align_pagesize(size_t x, int large);
void		*new_page(size_t size);

// extern void				*g_pages[3];
extern pthread_mutex_t	g_mutex[LARGE + 1];
extern t_tree			g_segments;
#endif
