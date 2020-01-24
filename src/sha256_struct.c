/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:52:37 by mnguyen           #+#    #+#             */
/*   Updated: 2019/01/14 14:59:36 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_md5.h"

void	set_w(t_sha256 *sha256_struct, int o)
{
	int i;

	i = 0;
	while (i < 16)
	{
		sha256_struct->w[i] =                                              \
			(sha256_struct->data_completed.bytes[i * 4 + o] << 24)		   \
			| (sha256_struct->data_completed.bytes[(i * 4) + 1 + o] << 16) \
			| (sha256_struct->data_completed.bytes[(i * 4) + 2 + o] << 8)  \
			| (sha256_struct->data_completed.bytes[(i * 4) + 3 + o]);
		i++;
	}
	while (i < 64)
	{
		sha256_struct->w[i] = (right_rotate(sha256_struct->w[i - 2], 17) \
			^ right_rotate(sha256_struct->w[i - 2], 19)					 \
			^ (sha256_struct->w[i - 2] >> 10)) + sha256_struct->w[i - 7] \
			+ (right_rotate(sha256_struct->w[i - 15], 7)				 \
			^ right_rotate(sha256_struct->w[i - 15], 18)				 \
			^ (sha256_struct->w[i - 15] >> 3)) + sha256_struct->w[i - 16];
		i++;
	}
}

void	set_data_out(t_sha256 *sha256_struct, enum e_command command)
{
	int i;

	i = 0;
	while (i < 4)
	{
		sha256_struct->data_out.bytes[i] = (sha256_struct->h0	   \
												>> (24 - i * 8)) & 0xff;
		sha256_struct->data_out.bytes[i + 4] = (sha256_struct->h1  \
												>> (24 - i * 8)) & 0xff;
		sha256_struct->data_out.bytes[i + 8] = (sha256_struct->h2  \
												>> (24 - i * 8)) & 0xff;
		sha256_struct->data_out.bytes[i + 12] = (sha256_struct->h3 \
												>> (24 - i * 8)) & 0xff;
		sha256_struct->data_out.bytes[i + 16] = (sha256_struct->h4 \
												>> (24 - i * 8)) & 0xff;
		sha256_struct->data_out.bytes[i + 20] = (sha256_struct->h5 \
												>> (24 - i * 8)) & 0xff;
		sha256_struct->data_out.bytes[i + 24] = (sha256_struct->h6 \
												>> (24 - i * 8)) & 0xff;
		if (command == SHA256)
			sha256_struct->data_out.bytes[i + 28] = (sha256_struct->h7 \
													>> (24 - i * 8)) & 0xff;
		i++;
	}
}

void	set_h(t_sha256 *sha256_struct, enum e_command command)
{
	if (command == SHA256)
	{
		sha256_struct->h0 = 0x6a09e667;
		sha256_struct->h1 = 0xbb67ae85;
		sha256_struct->h2 = 0x3c6ef372;
		sha256_struct->h3 = 0xa54ff53a;
		sha256_struct->h4 = 0x510e527f;
		sha256_struct->h5 = 0x9b05688c;
		sha256_struct->h6 = 0x1f83d9ab;
		sha256_struct->h7 = 0x5be0cd19;
	}
	else
	{
		sha256_struct->h0 = 0xC1059ED8;
		sha256_struct->h1 = 0x367CD507;
		sha256_struct->h2 = 0x3070DD17;
		sha256_struct->h3 = 0xF70E5939;
		sha256_struct->h4 = 0xFFC00B31;
		sha256_struct->h5 = 0x68581511;
		sha256_struct->h6 = 0x64F98FA7;
		sha256_struct->h7 = 0xBEFA4FA4;
	}
}

void	*set_sha224_256_struct(t_buffer data, enum e_command command)
{
	t_sha256 *sha256_struct;

	sha256_struct = malloc(sizeof(t_sha256));
	if (sha256_struct == NULL)
		error(MALLOC_FAILED, "");
	sha256_struct->k = set_k(sha256_struct->k);
	sha256_struct->w = malloc(sizeof(int) * 64);
	if (sha256_struct->w == NULL)
		error(MALLOC_FAILED, "");
	if (command == SHA256)
		sha256_struct->data_out.size = sizeof(int) * 8;
	else
		sha256_struct->data_out.size = sizeof(int) * 7;
	sha256_struct->data_out.bytes = malloc(sha256_struct->data_out.size);
	if (sha256_struct->data_out.bytes == NULL)
		error(MALLOC_FAILED, "");
	sha256_struct->data_completed = \
		set_data_completed(sha256_struct->data_completed, data, FALSE);
	set_h(sha256_struct, command);
	return ((void *)sha256_struct);
}
