/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rsautl.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 16:06:55 by mnguyen           #+#    #+#             */
/*   Updated: 2020/02/28 16:06:57 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_rsa.h"
#include "ssl_des.h"

void		read_inkey_file(t_args *args, t_buffer *inkey)
{
	if (!(args->opts & OPT_INKEY))
		error_free_args(RSAUTL_NO_INKEY, "", args);
	args->fd = open((const char *)args->inkey_file.bytes, O_RDONLY);
	(args->fd < 0) ? error_free_args(OPEN_FAILED, "", args) : 0;
	inkey->bytes = malloc(sizeof(unsigned char) * (DATA_SIZE_MAX + 1));
	(inkey->bytes == NULL) ? error_free_args(MALLOC_FAILED, "", args) : 0;
	inkey->size = read(args->fd, inkey->bytes, DATA_SIZE_MAX + 1);
	close(args->fd);
	if (inkey->size == (DATA_SIZE_MAX + 1) || inkey->size < 0 \
		|| inkey->size == 0)
		error_free_args(INVALID_RSAUTL_INKEY_FILE, "", args);
}

t_buffer	rsa_encode(t_args *args, t_buffer data, t_rsa rsa_struct)
{
	t_buffer	result;
	t_uint64	m;
	t_uint64	c;

	result.size = 8;
	result.bytes = malloc(sizeof(t_byte) * result.size);
	ft_bzero(result.bytes, 8);
	(result.bytes == NULL) ? error_free_args(MALLOC_FAILED, "", args) : 0;
	m = (t_uint128)bytes_to_uint64(data.bytes, data.size);
	if (m >= rsa_struct.n)
		error_free_args(RSAUTL_DATA_GREATER_THAN_MODULUS, "", args);
	c = mod_pow(m, rsa_struct.e, rsa_struct.n);
	rsautl_uint64_to_bytes(c, &result);
	return (result);
}

t_buffer	rsa_decode(t_args *args, t_buffer data, t_rsa rsa_struct)
{
	t_buffer	result;
	t_uint64	c;
	t_uint64	m;

	result.size = 8;
	result.bytes = malloc(sizeof(t_byte) * result.size);
	ft_bzero(result.bytes, 8);
	(result.bytes == NULL) ? error_free_args(MALLOC_FAILED, "", args) : 0;
	c = (t_uint128)bytes_to_uint64(data.bytes, data.size);
	if (c >= rsa_struct.n)
		error_free_args(RSAUTL_DATA_GREATER_THAN_MODULUS, "", args);
	m = mod_pow(c, rsa_struct.d, rsa_struct.n);
	rsautl_uint64_to_bytes(m, &result);
	return (result);
}

void		print_rsa_result(t_args *args, t_buffer result)
{
	if (args->opts & OPT_HEXDUMP)
		print_hexdump(result, args->fd);
	else
		print_buffer_fd(result, args->fd);
}

void		rsautl(t_args *args)
{
	t_buffer	data;
	t_buffer	inkey;
	t_rsa		rsa_struct;
	t_buffer	result;

	read_inkey_file(args, &inkey);
	set_data(args, &data);
	if (data.size > 8)
		error_free_args(RSAUTL_DATA_TOO_BIG, "", args);
	set_fd(args);
	decode_pem(args, inkey, &rsa_struct);
	if (args->opts & OPT_D)
		result = rsa_decode(args, data, rsa_struct);
	else
		result = rsa_encode(args, data, rsa_struct);
	print_rsa_result(args, result);
	close(args->fd);
	free(result.bytes);
	free_args(args);
}
