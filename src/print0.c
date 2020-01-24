/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:13:02 by mnguyen           #+#    #+#             */
/*   Updated: 2019/01/14 14:13:15 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_md5.h"

void	print_buffer_fd(t_buffer buf, int fd)
{
	int i;

	i = 0;
	while (i < buf.size)
	{
		write(fd, &buf.bytes[i], 1);
		i++;
	}
}

void	print_buffer(t_buffer buf)
{
	int i;

	i = 0;
	while (i < buf.size)
	{
		ft_putchar(buf.bytes[i]);
		i++;
	}
}

void	print_bufferr(t_buffer buf)
{
	int i;

	i = 0;
	while (i < buf.size)
	{
		write(2, &buf.bytes[i], 1);
		i++;
	}
}
