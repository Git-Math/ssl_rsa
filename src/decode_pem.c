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

int		get_asn1_private_begin(t_args *args, t_buffer data, t_rsa *rsa_struct)
{
	int		i;

	i = 0;
	while ((data.size - i >= 32) \
		&& (!(i == 0 || data.bytes[i - 1] == '\n') \
		|| ft_memcmp(data.bytes + i, "-----BEGIN RSA PRIVATE KEY-----\n", 32)))
		i++;
	if (data.size - i < 32)
		error_free_args(INVALID_RSA_PEM, "invalid private beginning.\n", args);
	i += 32;
	if (data.size - i >= 51 && !ft_memcmp(data.bytes + i, \
		"Proc-Type: 4,ENCRYPTED\nDEK-Info: DES-CBC,", 41))
	{
		rsa_struct->salt.size = 8;
		rsa_struct->salt.bytes = malloc(sizeof(t_byte) * rsa_struct->salt.size);
		ft_memcpy(rsa_struct->salt.bytes, data.bytes + i + 41, 8);
		if (data.bytes[i + 49] != '\n' || data.bytes[i + 50] != '\n')
			error_free_args(INVALID_RSA_PEM, "invalid des encrypt.\n", args);
		i += 51;
	}
	else
		rsa_struct->salt.size = 0;
	return (i);
}

/*
void	get_asn1_private_des(t_args *args, t_buffer data, t_rsa *rsa_struct)
{

}
*/

void	get_asn1_private(t_args *args, t_buffer data, t_rsa *rsa_struct)
{
	int		i;
	int		si;

	si = get_asn1_private_begin(args, data, rsa_struct);
	i = si;
	while ((i < data.size) && (data.bytes[i] != '-'))
		i++;
	if (((data.size - i) < 29) \
		|| ft_memcmp(data.bytes + i, "-----END RSA PRIVATE KEY-----", 29) \
		|| ((data.size - i - 29) > 0 && (data.bytes[i + 29] != '\n')))
		error_free_args(INVALID_RSA_PEM, "invalid private ending.\n", args);
	rsa_struct->asn164.size = i - si;
	rsa_struct->asn164.bytes = malloc(sizeof(t_byte) \
										* rsa_struct->asn164.size);
	if (rsa_struct->asn164.bytes == NULL)
		error_free_args(MALLOC_FAILED, "", args);
	ft_memcpy(rsa_struct->asn164.bytes, data.bytes + si, \
				rsa_struct->asn164.size);
	/* (rsa_struct->salt.size == 0) \
		? */rsa_struct->asn1 = base64_decode((void *)&rsa_struct->asn164);/* \
		: get_asn1_private_des(args, data, rsa_struct);*/
}

void	get_asn1_public(t_args *args, t_buffer data, t_rsa *rsa_struct)
{
	int		i;
	int		si;

	si = 0;
	while ((data.size - si >= 27) \
		&& (!(si == 0 || data.bytes[si - 1] == '\n') \
		|| ft_memcmp(data.bytes + si, "-----BEGIN PUBLIC KEY-----\n", 27)))
		si++;
	if (data.size - si < 27)
		error_free_args(INVALID_RSA_PEM, "invalid public beginning.\n", args);
	i = si + 27;
	while ((i < data.size) && (data.bytes[i] != '-'))
		i++;
	if (((data.size - i) < 24) \
		|| ft_memcmp(data.bytes + i, "-----END PUBLIC KEY-----", 24) \
		|| ((data.size - i - 24) > 0 && (data.bytes[i + 24] != '\n')))
		error_free_args(INVALID_RSA_PEM, "invalid public ending.\n", args);
	rsa_struct->asn164.size = i - si - 27;
	rsa_struct->asn164.bytes = malloc(sizeof(t_byte) \
										* rsa_struct->asn164.size);
	if (rsa_struct->asn164.bytes == NULL)
		error_free_args(MALLOC_FAILED, "", args);
	ft_memcpy(rsa_struct->asn164.bytes, data.bytes + 27 + si, \
				rsa_struct->asn164.size);
	rsa_struct->asn1 = base64_decode((void *)&rsa_struct->asn164);
}

void	decode_pem(t_args *args, t_buffer data, t_rsa *rsa_struct)
{
	(args->opts & OPT_PUBIN) ? get_asn1_public(args, data, rsa_struct) \
							: get_asn1_private(args, data, rsa_struct);
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
	if (args->opts & OPT_CHECK)
		check_rsa_key(args, rsa_struct);
}
