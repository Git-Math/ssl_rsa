/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsautl_util.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 19:12:03 by mnguyen           #+#    #+#             */
/*   Updated: 2020/02/28 19:12:04 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_rsa.h"

int		rsautl_uint64_size(t_uint64 n)
{
	t_uint64	size;

	size = 1;
	n >>= 8;
	while (n != 0)
	{
		n >>= 8;
		size += 1;
	}
	return (size);
}

void	rsautl_uint64_to_bytes(t_uint64 n, t_buffer *buf)
{
	t_uint64	size;

	size = rsautl_uint64_size(n);
	buf->size = size;
	while (size > 0)
	{
		buf->bytes[size - 1] = n & 0xFF;
		n >>= 8;
		size--;
	}
}

void	print_hexdump_hex(t_buffer buff, int fd)
{
	int				i;
	unsigned char	first;
	unsigned char	sec;

	i = 0;
	while (i < buff.size)
	{
		first = buff.bytes[i] >> 4;
		if (first < 10)
			ft_putuint64_fd(first, fd);
		else
			ft_putchar_fd(first - 10 + 'a', fd);
		sec = buff.bytes[i] & 0xf;
		if (sec < 10)
			ft_putuint64_fd(sec, fd);
		else
			ft_putchar_fd(sec - 10 + 'a', fd);
		i++;
		ft_putchar_fd(' ', fd);
	}
}

void	print_hexdump_chars(t_buffer buff, int fd)
{
	int	i;

	i = 0;
	while (i < buff.size)
	{
		if (buff.bytes[i] >= 32 && buff.bytes[i] <= 126)
			ft_putchar_fd(buff.bytes[i], fd);
		else
			ft_putchar_fd('.', fd);
		i++;
	}
}

void	print_hexdump(t_buffer buff, int fd)
{
	ft_putstr_fd("0000 - ", fd);
	print_hexdump_hex(buff, fd);
	ft_putstr_fd("  ", fd);
	print_hexdump_chars(buff, fd);
	ft_putchar_fd('\n', fd);
}
