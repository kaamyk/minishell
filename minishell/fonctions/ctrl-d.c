/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctrl-d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 12:36:30 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/23 12:37:06 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
     char *buffer = NULL;
     size_t bufsize = 0;
     ssize_t characters;
      
     characters = getline(&buffer, &bufsize, stdin);
     if (characters == -1)
     {
           printf("You entered CTRL+D\n");
     }
     free(buffer);
     return (0);
}
