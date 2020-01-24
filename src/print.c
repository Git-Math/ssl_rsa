/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:17:22 by mnguyen           #+#    #+#             */
/*   Updated: 2019/01/14 15:18:21 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_md5.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else if (n == 0)
		ft_putchar('0');
	else if (n < 0)
	{
		ft_putchar('-');
		ft_putnbr(-n);
	}
	else if (n > 0)
	{
		if (n / 10 > 0)
			ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
}

void	ft_putstr(char *s)
{
	while (*s != 0)
		ft_putchar(*(s++));
}

void	ft_putsterr(char *s)
{
	while (*s != 0)
		write(2, s++, 1);
}

void	print_buffer_hex(t_buffer buff)
{
	int				i;
	unsigned char	first;
	unsigned char	sec;

	i = 0;
	while (i < buff.size)
	{
		first = buff.bytes[i] >> 4;
		if (first < 10)
			ft_putnbr(first);
		else
			ft_putchar(first - 10 + 'a');
		sec = buff.bytes[i] & 0xf;
		if (sec < 10)
			ft_putnbr(sec);
		else
			ft_putchar(sec - 10 + 'a');
		i++;
	}
}
