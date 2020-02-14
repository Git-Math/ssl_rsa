/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decode_pem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 15:10:07 by mnguyen           #+#    #+#             */
/*   Updated: 2020/02/14 15:10:09 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_rsa.h"
#include "ssl_des.h"

static t_byte g_pub_start[20] = { 0x30, 0x0D, 0x06, 0x09, 0x2A, 0x86, 0x48, \
	0x86, 0xF7, 0x0D, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x13, 0x00, 0x30, \
	0x10 };

void		get_asn1(t_args *args, t_buffer data, t_rsa *rsa_struct)
{
	int		i;

	if ((data.size < 32) \
		|| ft_memcmp(data.bytes, "-----BEGIN RSA PRIVATE KEY-----\n", 32))
		error_free_args(INVALID_RSA_PEM, "invalid beginning.\n", args);
	i = 32;
	while ((i < data.size) && (data.bytes[i] != '-'))
		i++;
	if (((data.size - i) < 29) \
		|| ft_memcmp(data.bytes + i, "-----END RSA PRIVATE KEY-----", 29) \
		|| ((data.size - i - 29) > 0 && (data.bytes[i + 29] != '\n')))
		error_free_args(INVALID_RSA_PEM, "invalid ending.\n", args);
	rsa_struct->asn164.size = i - 32;
	rsa_struct->asn164.bytes = malloc(sizeof(t_byte) \
										* rsa_struct->asn164.size);
	if (rsa_struct->asn164.bytes == NULL)
		error_free_args(MALLOC_FAILED, "", args);
	ft_memcpy(rsa_struct->asn164.bytes, data.bytes + 32, \
				rsa_struct->asn164.size);
	rsa_struct->asn1 = base64_decode((void *)&rsa_struct->asn164);
}

t_uint64	decode_asn1_value(t_args *args, t_buffer asn1, int *i)
{
	t_uint64	value;
	int			size;

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
	{
		value += (t_uint64)asn1.bytes[*i] << ((size - 1) * 8);
		size--;
		(*i)++;
	}
	return (value);
}
//TEMP for private and public, check that we don't go out of memory, and check the end of asn1
void		decode_asn1_private(t_args *args, t_rsa *rsa_struct)
{
	int		i;

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

void 		decode_asn1_public(t_args *args, t_rsa *rsa_struct)
{
	int		i;

	//TEMP fix decode, handle | to pass throw ./ft_ssl succesive
	if (rsa_struct->asn1.bytes[0] != 0x30)
		error_free_args(INVALID_RSA_ASN1, "must be a sequence.\n", args);
	if (rsa_struct->asn1.bytes[1] != (rsa_struct->asn1.size - 2))
		error_free_args(INVALID_RSA_ASN1, "invalid sequence size.\n", args);
	if (ft_memcmp(rsa_struct->asn1.bytes + 2, g_pub_start, 20))
		error_free_args(INVALID_RSA_ASN1, "invalid pubblic start.\n", args);
	i = 22;
	rsa_struct->n = decode_asn1_value(args, rsa_struct->asn1, &i);
	rsa_struct->e = decode_asn1_value(args, rsa_struct->asn1, &i);
}

void		decode_pem(t_args *args, t_buffer data, t_rsa *rsa_struct)
{
	get_asn1(args, data, rsa_struct);
	(args->opts & OPT_PUBIN) ? decode_asn1_public(args, rsa_struct) \
							: decode_asn1_private(args, rsa_struct);
	if (args->opts & OPT_TEXT)
		(args->opts & OPT_PUBIN) ? print_rsa_struct_public(args, rsa_struct) \
								: print_rsa_struct_private(args, rsa_struct);
	if (args->opts & OPT_MODULUS)
	{
		ft_putstr_fd("Modulus=", args->fd);
		ft_putuint64_hex_fd(rsa_struct->n, FALSE, args->fd);
		ft_putstr_fd("\n", args->fd);
	}
}
