/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   break_rsa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 13:46:28 by mnguyen           #+#    #+#             */
/*   Updated: 2020/03/06 13:46:29 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_rsa.h"

t_uint64	mod_pow_64(t_uint64 n, t_uint64 p, t_uint64 m)
{
	t_uint64	r;

	r = 1;
	while (p)
	{
		if (p & 1)
			r = (r * n) % m;
		n = (n * n) % m;
		p >>= 1;
	}
	return (r);
}

t_uint64	middle_search(t_hash_table *hash_table, t_rsa rsa_struct, \
							t_uint64 c)
{
	t_uint64	m2;
	t_uint64	key;
	t_uint64	val;

	m2 = 0;
	while (m2 < hash_table->size)
	{
		key = mod_inverse(mod_pow_64(m2, rsa_struct.e, rsa_struct.n)\
			, rsa_struct.n, FALSE) * c % rsa_struct.n;
		if (key != 0)
		{
			val = hash_search(hash_table, key);
			if (val != 0)
				return (val);
		}
		m2++;
	}
	return (0);
}

t_uint64	fill_hash_table(t_hash_table *hash_table, t_rsa rsa_struct,\
	t_uint64 c)
{
	t_uint64	key;
	t_uint64	val;

	val = 0;
	while (val < hash_table->size)
	{
		key = mod_pow_64(val, rsa_struct.e, rsa_struct.n);
		if (key == c)
			return (val);
		hash_insert(hash_table, key, val);
		val++;
	}
	return (0);
}

t_buffer	break_rsa_decode(t_args *args, t_buffer data, t_rsa rsa_struct)
{
	t_buffer		result;
	t_uint64		c;
	t_uint64		m;
	t_hash_table	*hash_table;

	result.size = 8;
	result.bytes = malloc(sizeof(t_byte) * result.size);
	ft_bzero(result.bytes, 8);
	(result.bytes == NULL) ? error_free_args(MALLOC_FAILED, "", args) : 0;
	c = (t_uint128)bytes_to_uint64(data.bytes, data.size);
	if (c >= rsa_struct.n)
		error_free_args(BREAK_RSA_DATA_GREATER_THAN_MODULUS, "", args);
	hash_table = create_hash_table((1 << 24) - 1);
	m = fill_hash_table(hash_table, rsa_struct, c);
	if (m == 0)
		m = middle_search(hash_table, rsa_struct, c);
	free_hash_table(hash_table);
	if (m == 0)
		error_free_args(BREAK_RSA_FAILED, "", args);
	rsautl_uint64_to_bytes(m, result.bytes);
	return (result);
}

void		break_rsa(t_args *args)
{
	t_buffer	data;
	t_buffer	inkey;
	t_rsa		rsa_struct;
	t_buffer	result;

	read_inkey_file(args, &inkey);
	set_data(args, &data);
	if (data.size > 8)
		error_free_args(BREAK_RSA_DATA_TOO_BIG, "", args);
	set_fd(args);
	args->opts = args->opts | OPT_PUBIN;
	decode_pem(args, inkey, &rsa_struct);
	result = break_rsa_decode(args, data, rsa_struct);
	print_rsa_result(args, result);
	close(args->fd);
	free(result.bytes);
	free_args(args);
}
