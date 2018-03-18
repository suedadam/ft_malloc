/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 03:05:35 by asyed             #+#    #+#             */
/*   Updated: 2018/03/17 03:06:25 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>
#include <stdlib.h>
#include <unistd.h>

#define M (1024 * 1024)

void print(char *s)
{
   write(1, s, strlen(s));
}

int     main()
{
   char *addr1;
   char *addr3;

   addr1 = (char*)malloc(16*M);
   strcpy(addr1, "Bonjours\n");
   print(addr1);
   addr3 = (char*)realloc(addr1, 128*M);
   addr3[127*M] = 42;
   print(addr3);
   return (0);
}