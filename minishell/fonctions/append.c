/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 19:01:29 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/23 19:01:32 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<fcntl.h>
  
// int main()
// {
//     int file_desc = open("test.txt",O_WRONLY | O_APPEND);
      
//     // here the newfd is the file descriptor of stdout (i.e. 1)
//     dup2(file_desc, 1) ; 
          
//     // All the printf statements will be written in the file
//     // "test.txt"
//     printf("I will be printed in the file test.txt\n");
      
// return 0;
// }

int main(int argc, char **argv)
{
	int pid, status;
	int newfd;	/* new file descriptor */

	// if (argc != 2) {
	// 	fprintf(stderr, "usage: %s output_file\n", argv[0]);
	// 	exit(1);
	// }
	if ((newfd = open(argv[1], O_CREAT|O_APPEND|O_WRONLY, 0644)) < 0) {
		perror(argv[1]);	/* open failed */
		exit(1);
	}

	dup2(newfd, 1); 

	printf("%s\n", argv[2]);
	exit(0);
}
