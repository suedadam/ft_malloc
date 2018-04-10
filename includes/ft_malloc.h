/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 15:42:46 by asyed             #+#    #+#             */
/*   Updated: 2018/04/10 00:28:44 by asyed            ###   ########.fr       */
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
# define CLEAN_INTERVAL 5
# define MAX_PER_PAGE 300
# define MAXPAGES 65536 //Worst case ~3GB allocated before running out.
# define TINY 128
# define LARGE 2048
# define PAGESIZE(x) ((x + sizeof(t_header)) * MAX_PER_PAGE)
# define PROT_ALL (PROT_READ | PROT_WRITE | PROT_EXEC)
# define FT_MAP_ANON (MAP_ANONYMOUS | MAP_PRIVATE | MAP_NOCACHE)

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

typedef struct	s_info
{
	void	*page_start;
	void	*pageid;
}				t_info;

typedef struct	s_tree
{
	t_header	*avail_segs[LARGE];
}				t_tree;

int			kill_cleaner(t_header *mem);
uint8_t		chksum(void *mem);
int			index_calc(size_t size);
int			index2size(uint8_t index);
int			valid_chksum(void *ptr);
void		free(void *ptr);
void		*malloc(size_t size);
void		*realloc(void *ptr, size_t size);
size_t		align_pagesize(size_t x, int large);
size_t		guess_pagesize(uint8_t pageid);
void		*new_page(size_t size);

pthread_t				pageid[MAXPAGES];
extern t_tree			g_segments;
#endif
