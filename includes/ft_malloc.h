/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 15:42:46 by asyed             #+#    #+#             */
/*   Updated: 2018/03/19 16:13:46 by asyed            ###   ########.fr       */
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
	size_t		len;
	uint8_t		used:1;
	uint8_t		index:2;
	uint8_t		chksum;
	void		*page_start;
	void		*next_page;
}				t_header;

void			free(void *ptr);
void			*malloc(size_t size);
void			*realloc(void *ptr, size_t size);
void			*size_spacer(int page_index, size_t pagesize, size_t size);
void			*large_alloc(size_t size);
void			*find_space(void *curr_page, size_t pagesize, size_t req_len);
int				get_memseg_size(uint8_t index);
void			*init_page(size_t pagesize);
int				next_page(t_header **l_page, void **curr_page, size_t pagesize);
int				align_pagesize(size_t x, int large);
int				valid_chksum(void *l_ptr);
uint8_t			chksum(void *mem);
void			show_alloc_mem(void);
void			print_pageheader(int page_index, size_t *total);
void			flip_page(t_header **l_page, void **curr_page, size_t pagesize);
void			*alloc_large(int page_index, size_t pagesize, size_t req_len);
void			update_prev(void *prev, void *next);
void			cleanup_tty(void);
int				non_allocated(void *ptr, int page_index);

extern void				*g_pages[3];
extern pthread_mutex_t	g_mutex[3];

#endif
