/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genrsa_key_buffer.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 14:42:19 by mnguyen           #+#    #+#             */
/*   Updated: 2020/02/06 14:42:20 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_rsa.h"

int			uint64_size(t_uint64 n)
{
	t_uint64	size;

	size = ((n == 0) ? 1 : 0) ;
	while (n != 0)
	{
		n >>= 8;
		size += 1;
	}
	return (size);
}

void 		uint64_to_bytes(t_uint64 n, t_byte *bytes)
{
	t_uint64	size;

	size = uint64_size(n);
	bytes[0] = (t_byte)0;
	while (size > 0)
	{
		bytes[size - 1] = n & 0xFF;
		n >>= 8;
		size--;
	}
}

void		key_add_uint64(t_uint64 n, t_byte *bytes, int *shift)
{
	t_uint64	size;

	size = uint64_size(n);
	uint64_to_bytes(2, bytes + *shift);
	*shift += uint64_size(2);
	uint64_to_bytes(size, bytes + *shift);
	*shift += uint64_size(size);
	uint64_to_bytes(n, bytes + *shift);
	*shift += size;
}

t_buffer	genrsa_key_buffer(t_genrsa genrsa_struct)
{
	t_buffer	key;
	int			shift;

	key.size = 21 + uint64_size(genrsa_struct.n) + uint64_size(genrsa_struct.e)\
		+ uint64_size(genrsa_struct.d) + uint64_size(genrsa_struct.p) \
		+ uint64_size(genrsa_struct.q) + uint64_size(genrsa_struct.d \
		% (genrsa_struct.p - 1)) + uint64_size(genrsa_struct.d \
		% genrsa_struct.q - 1) + uint64_size(genrsa_struct.l);
	key.bytes = (t_byte *)malloc(sizeof(t_byte) * key.size);
	(key.bytes == NULL) ? error(MALLOC_FAILED, "") : 0;
	shift = 0;
	uint64_to_bytes(30, key.bytes + shift);
	shift += uint64_size(30);
	uint64_to_bytes(key.size - 2, key.bytes + shift);
	shift += uint64_size(key.size - 2);
	key_add_uint64(0, key.bytes, &shift);
	key_add_uint64(genrsa_struct.n, key.bytes, &shift);
	key_add_uint64(genrsa_struct.e, key.bytes, &shift);
	key_add_uint64(genrsa_struct.d, key.bytes, &shift);
	key_add_uint64(genrsa_struct.p, key.bytes, &shift);
	key_add_uint64(genrsa_struct.q, key.bytes, &shift);
	key_add_uint64(genrsa_struct.d % (genrsa_struct.p - 1), key.bytes, &shift);
	key_add_uint64(genrsa_struct.d % (genrsa_struct.q - 1), key.bytes, &shift);
	key_add_uint64(genrsa_struct.l, key.bytes, &shift);
	return (key);
}
