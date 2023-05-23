/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvincen <anvincen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 14:16:38 by xuluu             #+#    #+#             */
/*   Updated: 2023/05/23 17:30:45 by anvincen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>

void	ft_putchar_fd(char c, int fd);

void	ft_putstr_fd(char *s, int fd);

void	ft_putnbr_fd(int n, int fd);

int		ft_isdigit(int character);

int		ft_atoi(const char *nptr);

void	ft_bzero(void *s, size_t n);

void	*ft_calloc(size_t nmemb, size_t size);

char	*ft_itoa(int n);

char	*ft_strdup(const char *s);

/*ici*/
size_t	ft_strlen(const char *str);

int		ft_strncmp(const char *s1, const char *s2, size_t n);

char	**ft_split(char const *s, char c);

char	*ft_strnstr(const char *big, const char *little, size_t len);

char	*ft_strchr(const char *s, int c); //find the first character

char	*ft_strrchr(const char *s, int c); //find the last character

void	*ft_memset(void *s, int c, size_t n);

char	*ft_strjoin(char const *s1, char const *s2);

#endif
