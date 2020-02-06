/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rsa_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:15:14 by mnguyen           #+#    #+#             */
/*   Updated: 2020/02/06 17:15:16 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_rsa.h"
#include "ssl_des.h"

void	print_rsa_key(t_args *args, t_buffer key)
{
	t_buffer	key64;

	key64 = base64_encode((void *)&key);
	free(key.bytes);
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
	write(args->fd, "-----BEGIN RSA PRIVATE KEY-----\n", 32);
	print_base64_encode_buffer0(args, key64);
	write(args->fd, "-----END RSA PRIVATE KEY-----\n", 30);
	close(args->fd);
	free(key64.bytes);
}