/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsa.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 15:12:10 by mnguyen           #+#    #+#             */
/*   Updated: 2020/02/13 15:12:12 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_rsa.h"
#include "ssl_des.h"

void		set_data(t_args *args, t_buffer *data)
{
	if (args->opts & OPT_I)
	{
		args->fd = open((const char *)args->data[0].bytes, O_RDONLY);
		(args->fd < 0) ? error_free_args(OPEN_FAILED, "", args) : 0;
		data->bytes = malloc(sizeof(unsigned char) * (DATA_SIZE_MAX + 1));
		(data->bytes == NULL) ? error_free_args(MALLOC_FAILED, "", args) : 0;
		data->size = read(args->fd, data->bytes, DATA_SIZE_MAX + 1);
		close(args->fd);
		if (data->size == (DATA_SIZE_MAX + 1) || data->size < 0 \
			|| data->size == 0)
			error_free_args(INVALID_RSA_INPUT_FILE, "", args);
	}
	else
	{
		data->size = args->data[0].size;
		data->bytes = malloc(sizeof(t_byte) * data->size);
		(data->bytes == NULL) ? error_free_args(MALLOC_FAILED, "", args) : 0;
		ft_memcpy(data->bytes, args->data[0].bytes, data->size);
	}
}

void		set_fd(t_args *args)
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
			args->fd = 1;
		}
	}
	else
		args->fd = 1;
}

void		rsa(t_args *args)
{
	t_buffer	data;
	t_rsa		rsa_struct;
	t_genrsa	genrsa_struct;
	t_buffer	key;

	set_data(args, &data);
	set_fd(args);
	decode_pem(args, data, &rsa_struct);
	if (!(args->opts & OPT_NOOUT))
	{
		ft_putsterr("writing RSA key\n");
		genrsa_struct.n = rsa_struct.n;
		genrsa_struct.e = rsa_struct.e;
		genrsa_struct.d = rsa_struct.d;
		genrsa_struct.p = rsa_struct.p;
		genrsa_struct.q = rsa_struct.q;
		key = ((args->opts & OPT_PUBIN) || (args->opts & OPT_PUBOUT)) \
								? rsa_public_key_buffer(genrsa_struct) \
								: genrsa_key_buffer(genrsa_struct);
		print_rsa_key(args, key, \
			!((args->opts & OPT_PUBIN) || (args->opts & OPT_PUBOUT)), TRUE);
	}
	free_args(args);
}
