/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xuluu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 10:31:14 by xuluu             #+#    #+#             */
/*   Updated: 2022/11/17 10:54:03 by xuluu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_len(int n)
{
	size_t	len;

	len = 0;
	if (n >= 0 && n <= 9)
		len++;
	else
	{
		len += count_len(n / 10);
		len += count_len(n % 10);
	}
	return (len);
}

size_t	check_n(int n)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		len++;
		if (n == -2147483648)
		{
			len++;
			n = 147483648;
		}
		else
			n *= -1;
	}
	len += count_len(n);
	return (len);
}

size_t	count(char *number, int n, size_t t)
{
	size_t	m;

	m = 0;
	if (n < 0)
	{
		m++;
		number[0] = '-';
		if (n != -2147483648)
			n *= -1;
	}
	if (n == -2147483648)
	{
		m++;
		number[1] = 2 + 48;
		n = 147483648;
	}
	if (t == 1)
		return (m);
	else
		return (n);
}

char	*ft_itoa(int n)
{
	char	*number;
	size_t	len;
	size_t	i;
	size_t	m;

	len = check_n(n);
	number = (char *)malloc((len + 1) * sizeof(char));
	if (!number)
		return (0);
	m = count(number, n, 1);
	n = count(number, n, 0);
	i = len;
	while (len >= m && len <= 65535)
	{
		if (i == len)
			number[len] = 0;
		else
		{
			number[len] = (n % 10) + 48;
			n = n / 10;
		}
		len--;
	}
	return (number);
}
