/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode_asn1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 13:48:42 by mnguyen           #+#    #+#             */
/*   Updated: 2020/02/20 13:48:43 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_rsa.h"

static t_byte g_pub_start[20] = { 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, \
	0x86, 0xF7, 0x0D, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x13, 0x00, 0x30, \
	0x10 };

t_buffer	rsa_public_key_buffer(t_genrsa genrsa_struct)
{
	t_buffer	key;
	int			shift;

	key.size = 26 + uint64_size(genrsa_struct.n) + uint64_size(genrsa_struct.e);
	key.bytes = (t_byte *)malloc(sizeof(t_byte) * key.size);
	(key.bytes == NULL) ? error(MALLOC_FAILED, "") : 0;
	shift = 0;
	uint64_to_bytes(0x30, key.bytes + shift);
	shift += 1;
	uint64_to_bytes(key.size - 2, key.bytes + shift);
	shift += 1;
	ft_memcpy(key.bytes + shift, g_pub_start, 20);
	shift += 20;
	key_add_uint64(genrsa_struct.n, key.bytes, &shift);
	key_add_uint64(genrsa_struct.e, key.bytes, &shift);
	return (key);
}

t_uint64	decode_asn1_value(t_args *args, t_buffer asn1, int *i)
{
	t_uint64	value;
	int			size;

	if (asn1.size <= (*i) + 2)
		error_free_args(INVALID_RSA_ASN1, "invalid asn1 value size.\n", args);
	if (asn1.bytes[*i] != 0x02)
		error_free_args(INVALID_RSA_ASN1, "invalid value type.\n", args);
	(*i)++;
	size = asn1.bytes[*i];
	if (size > 0x09 \
		|| (size == 0x09 && (asn1.bytes[(*i) + 1] != 0x00)) \
		|| ((size + (*i)) >= asn1.size))
		error_free_args(INVALID_RSA_ASN1, "value size too big.\n", args);
	(*i)++;
	if (size == 9)
	{
		size--;
		(*i)++;
	}
	value = 0;
	while (size > 0)
		value += (t_uint64)asn1.bytes[(*i)++] << (((size--) - 1) * 8);
	return (value);
}

void		decode_asn1_private(t_args *args, t_rsa *rsa_struct)
{
	int		i;

	if (rsa_struct->asn1.size <= 4)
		error_free_args(INVALID_RSA_ASN1, "invalid asn1 size.\n", args);
	if (rsa_struct->asn1.bytes[0] != 0x30)
		error_free_args(INVALID_RSA_ASN1, "must be a sequence.\n", args);
	if (rsa_struct->asn1.bytes[1] != (rsa_struct->asn1.size - 2))
		error_free_args(INVALID_RSA_ASN1, "invalid sequence size.\n", args);
	if (rsa_struct->asn1.bytes[2] != 0x02)
		error_free_args(INVALID_RSA_ASN1, "invalid version type.\n", args);
	if (rsa_struct->asn1.bytes[3] != 0x01)
		error_free_args(INVALID_RSA_ASN1, "version size too big.\n", args);
	i = 5;
	rsa_struct->n = decode_asn1_value(args, rsa_struct->asn1, &i);
	rsa_struct->e = decode_asn1_value(args, rsa_struct->asn1, &i);
	rsa_struct->d = decode_asn1_value(args, rsa_struct->asn1, &i);
	rsa_struct->p = decode_asn1_value(args, rsa_struct->asn1, &i);
	rsa_struct->q = decode_asn1_value(args, rsa_struct->asn1, &i);
	rsa_struct->exp1 = decode_asn1_value(args, rsa_struct->asn1, &i);
	rsa_struct->exp2 = decode_asn1_value(args, rsa_struct->asn1, &i);
	rsa_struct->coef = decode_asn1_value(args, rsa_struct->asn1, &i);
}

void		decode_asn1_public(t_args *args, t_rsa *rsa_struct)
{
	int		i;

	if (rsa_struct->asn1.size <= 21)
		error_free_args(INVALID_RSA_ASN1, "invalid asn1 size.\n", args);
	if (rsa_struct->asn1.bytes[0] != 0x30)
		error_free_args(INVALID_RSA_ASN1, "must be a sequence.\n", args);
	if (rsa_struct->asn1.bytes[1] != (rsa_struct->asn1.size - 2))
		error_free_args(INVALID_RSA_ASN1, "invalid sequence size.\n", args);
	if (ft_memcmp(rsa_struct->asn1.bytes + 2, g_pub_start, 20))
		error_free_args(INVALID_RSA_ASN1, "invalid public start.\n", args);
	i = 22;
	rsa_struct->n = decode_asn1_value(args, rsa_struct->asn1, &i);
	rsa_struct->e = decode_asn1_value(args, rsa_struct->asn1, &i);
}
