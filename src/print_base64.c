/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_base64.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 00:38:35 by mnguyen           #+#    #+#             */
/*   Updated: 2019/11/07 00:38:36 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

void	print_base64_encode_buffer0(t_args *args, t_buffer buf)
{
	int i;

	i = 0;
	while (i < buf.size)
	{
		if (!(args->opts & OPT_D) && i % 64 == 0 && i != 0)
			write(args->fd, "\n", 1);
		write(args->fd, &buf.bytes[i], 1);
		i++;
	}
	if (!(args->opts & OPT_D))
		write(args->fd, "\n", 1);
}

void	print_base64_buffer(t_args *args, t_buffer buf)
{
	if (args->opts & OPT_O)
	{
		args->fd = open((const char *)args->out_file.bytes, \
			O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (args->fd < 0)
		{
			ft_putsterr("ft_ssl: ");
			print_bufferr(args->out_file);
			ft_putsterr(": couldn't open the file\n");
			return ;
		}
	}
	else
		args->fd = 1;
	print_base64_encode_buffer0(args, buf);
	close(args->fd);
}

void	print_des_result(t_args *args, t_buffer result)
{
	if (args->opts & OPT_O)
	{
		args->fd = open((const char *)args->out_file.bytes, \
			O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (args->fd < 0)
		{
			ft_putsterr("ft_ssl: ");
			print_bufferr(args->out_file);
			ft_putsterr(": couldn't open the file\n");
			return ;
		}
	}
	else
		args->fd = 1;
	if (args->opts & OPT_A)
		print_base64_encode_buffer0(args, result);
	else
		print_buffer_fd(result, args->fd);
	close(args->fd);
}
