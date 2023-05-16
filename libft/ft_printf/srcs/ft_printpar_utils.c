/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printpar_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antoine <antoine@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 19:09:46 by anvincen          #+#    #+#             */
/*   Updated: 2023/01/25 14:47:40 by antoine          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#define BASE_LC "0123456789abcdef"
#define BASE_UC "0123456789ABCDEF"
#define BASE_OCT "01234567"

void	ft_putnbr_base_oct(unsigned int n, char **res, int len_n)
{
	int	i;

	i = 0;
	while (res[0][i])
		++i;
	if (n != 0)
	{
		while (n != 0)
		{
			res[0][i + len_n - 1] = BASE_OCT[n % 8];
			n /= 8;
			--len_n;
		}
	}
	else
		res[0][i] = '0';
}

void	ft_putnbr_base_hex(size_t n, char **res, int len_n, char *par)
{
	char	last_c;
	int		i;

	i = 0;
	last_c = par[ft_strlen(par) - 1];
	while (res[0][i])
		++i;
	if (n != 0)
	{
		while (n > 0)
		{
			if (last_c == 'x' || last_c == 'p')
				res[0][i + len_n - 1] = BASE_LC[n % 16];
			else if (last_c == 'X')
				res[0][i + len_n - 1] = BASE_UC[n % 16];
			n /= 16;
			--len_n;
		}
	}
	else
		res[0][i] = '0';
}

char	*ft_itoa_u(unsigned int n)
{
	long	nb;
	int		len;
	char	*res;

	nb = n;
	len = ft_nblen_u(n);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	res[len] = 0;
	if (nb == 0)
		res[0] = '0';
	while (nb > 0)
	{
		len--;
		res[len] = nb % 10 + '0';
		nb /= 10;
	}
	return (res);
}

int	ft_nblen_hex(size_t n)
{
	int		len;

	if (n == 0)
		return (1);
	len = 0;
	while (n > 0)
	{
		len++;
		n /= 16;
	}
	return (len);
}

int	ft_strchr_str(char *s, char *to_find)
{
	int	i;
	int	j;

	if (!s || !to_find)
		return (0);
	i = 0;
	while (to_find[i])
	{
		j = 0;
		while (s[j])
		{
			if (to_find[i] == s[j])
				return (1);
			++j;
		}
		++i;
	}
	return (0);
}
