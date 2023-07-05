/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:17:51 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/19 17:17:55 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
 
int main()
{
    int check;

    check = 0;
    if (fork()== 0)
    {
        printf("HC: hello from child\n");
        check = 1;
    }
    else
    {
        wait(NULL);
        printf("HP: hello from parent\n");
        printf("%d\n", check);
    }
 
    printf("Bye\n");
    return 0;
}
