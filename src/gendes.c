/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gendes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:09:28 by mnguyen           #+#    #+#             */
/*   Updated: 2020/03/05 15:09:29 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_rsa.h"

void		print_des_key(t_args *args, t_gendes gendes_struct)
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
	ft_putstr_fd("des key(hex): ", args->fd);
	print_buffer_hex_fd(gendes_struct.key, args->fd);
	ft_putstr_fd("\ndes iv(hex): ", args->fd);
	print_buffer_hex_fd(gendes_struct.iv, args->fd);
	ft_putchar_fd('\n', args->fd);
	close(args->fd);
	free(gendes_struct.key.bytes);
	free(gendes_struct.iv.bytes);
}

t_gendes	gendes(void)
{
	t_gendes	gendes_struct;

	ft_putsterr("Generating DES key\n");
	gendes_struct.key.size = 8;
	gendes_struct.key.bytes = rand_bytes(gendes_struct.key.size);
	gendes_struct.iv.size = 8;
	gendes_struct.iv.bytes = rand_bytes(gendes_struct.iv.size);
	return (gendes_struct);
}
