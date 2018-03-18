/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 03:09:27 by asyed             #+#    #+#             */
/*   Updated: 2018/03/17 03:10:23 by asyed            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void print(char *s)
{
   write(1, s, strlen(s));
}

int    main()
{
   char *addr;

   addr = malloc(16);
   free(NULL);
   printf("Not there!\n");
   free((void *)addr + 5);
   printf("there?\n");
   if (realloc((void *)addr + 5, 10) == NULL)
    print("Bonjours\n");
}
