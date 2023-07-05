/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:23:53 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/19 17:23:56 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

void    ex()
{
    printf("The number of times ‘hello’ is printed is equal to the number of processes created.\
        Total Number of Processes = 2n, where n is the number of fork system calls.\
        So here n = 3, 2^3 = 8\n");
}

int main()
{
    ex();
    fork();
    fork();
    fork();
    printf("hello\n");
    return 0;
}
