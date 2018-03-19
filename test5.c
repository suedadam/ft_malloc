/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test5.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asyed <asyed@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/17 03:09:27 by asyed             #+#    #+#             */
/*   Updated: 2018/03/19 15:32:40 by asyed            ###   ########.fr       */
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
   free((void *)addr + 5);
   if (realloc((void *)addr + 5, 10) == NULL)
    print("Bonjours\n");
}
