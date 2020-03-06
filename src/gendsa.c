/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gendsa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:09:20 by mnguyen           #+#    #+#             */
/*   Updated: 2020/03/05 15:09:21 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_rsa.h"
#include "ssl_des.h"

void		print_dsa_key(t_args *args, t_buffer key)
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
	write(args->fd, "-----BEGIN DSA PRIVATE KEY-----\n", 32);
	print_base64_encode_buffer0(args, key64);
	write(args->fd, "-----END DSA PRIVATE KEY-----\n", 30);
	close(args->fd);
	free(key64.bytes);
}

int			calc_key_size_dsa(t_gendsa gendsa_struct)
{
	int		size;

	size = 15 + uint64_size(gendsa_struct.x) + uint64_size(gendsa_struct.y)\
		+ uint64_size(gendsa_struct.p) + uint64_size(gendsa_struct.q)\
		+ uint64_size(gendsa_struct.g);
	return (size);
}

t_buffer	gendsa_key_buffer(t_gendsa gendsa_struct)
{
	t_buffer	key;
	int			shift;

	key.size = calc_key_size_dsa(gendsa_struct);
	key.bytes = (t_byte *)malloc(sizeof(t_byte) * key.size);
	(key.bytes == NULL) ? error(MALLOC_FAILED, "") : 0;
	shift = 0;
	uint64_to_bytes(0x30, key.bytes + shift);
	shift += 1;
	uint64_to_bytes(key.size - 2, key.bytes + shift);
	shift += 1;
	key_add_uint64(0, key.bytes, &shift);
	key_add_uint64(gendsa_struct.x, key.bytes, &shift);
	key_add_uint64(gendsa_struct.y, key.bytes, &shift);
	key_add_uint64(gendsa_struct.p, key.bytes, &shift);
	key_add_uint64(gendsa_struct.q, key.bytes, &shift);
	key_add_uint64(gendsa_struct.g, key.bytes, &shift);
	return (key);
}

t_buffer	gendsa(void)
{
	t_gendsa	gendsa_struct;

	ft_putsterr("Generating DSA key, 64 bits\n");
	gendsa_struct.p = 9849842530271717657ul;
	gendsa_struct.q = 40957729825487ul;
	gendsa_struct.g = 6218784445592772903ul;
	gendsa_struct.x = rand_uint64(1, gendsa_struct.q - 1);
	gendsa_struct.y = mod_pow(gendsa_struct.g, \
								gendsa_struct.x, gendsa_struct.p);
	return (gendsa_key_buffer(gendsa_struct));
}
