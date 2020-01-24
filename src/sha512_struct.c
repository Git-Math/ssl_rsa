/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:59:55 by mnguyen           #+#    #+#             */
/*   Updated: 2019/01/14 17:47:00 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_md5.h"

t_buffer	set_data_completed512(t_buffer data_completed, t_buffer data)
{
	size_t		b;
	int			i;

	data_completed.size = data.size + 17 + (128 - (data.size + 17) % 128) % 128;
	data_completed.bytes = malloc(data_completed.size);
	if (data_completed.bytes == NULL)
		error(MALLOC_FAILED, "");
	data_completed.bytes = ft_memset(data_completed.bytes \
									, 0, data_completed.size);
	data_completed.bytes = ft_memcpy(data_completed.bytes \
									, data.bytes, data.size);
	data_completed.bytes[data.size] = 1 << 7;
	b = data.size * 8;
	i = 0;
	while (i < 8)
	{
		ft_memcpy(data_completed.bytes + data_completed.size - 1 - i \
					, ((t_byte *)&b) + i, 1);
		i++;
	}
	return (data_completed);
}

void		set_w512(t_sha512 *sha512_struct, int o)
{
	int i;

	i = -1;
	while (++i < 16)
	{
		sha512_struct->w[i] =                                                \
	((t_uint64)sha512_struct->data_completed.bytes[i * 8 + o] << 56)		 \
	| ((t_uint64)sha512_struct->data_completed.bytes[(i * 8) + 1 + o] << 48) \
	| ((t_uint64)sha512_struct->data_completed.bytes[(i * 8) + 2 + o] << 40) \
	| ((t_uint64)sha512_struct->data_completed.bytes[(i * 8) + 3 + o] << 32) \
	| ((t_uint64)sha512_struct->data_completed.bytes[(i * 8) + 4 + o] << 24) \
	| ((t_uint64)sha512_struct->data_completed.bytes[(i * 8) + 5 + o] << 16) \
	| ((t_uint64)sha512_struct->data_completed.bytes[(i * 8) + 6 + o] << 8)  \
	| ((t_uint64)sha512_struct->data_completed.bytes[(i * 8) + 7 + o]);
	}
	while (i < 80)
	{
		sha512_struct->w[i] = (right_rotate_long(sha512_struct->w[i - 2], 19) \
			^ right_rotate_long(sha512_struct->w[i - 2], 61)				  \
			^ (sha512_struct->w[i - 2] >> 6)) + sha512_struct->w[i - 7]		  \
			+ (right_rotate_long(sha512_struct->w[i - 15], 1)				  \
			^ right_rotate_long(sha512_struct->w[i - 15], 8)				  \
			^ (sha512_struct->w[i - 15] >> 7)) + sha512_struct->w[i - 16];
		i++;
	}
}

void		set_data_out512(t_sha512 *sha512_struct, enum e_command command)
{
	int i;

	i = -1;
	while (++i < 8)
	{
		sha512_struct->data_out.bytes[i] = (sha512_struct->h0	   \
												>> (56 - i * 8)) & 0xff;
		sha512_struct->data_out.bytes[i + 8] = (sha512_struct->h1  \
												>> (56 - i * 8)) & 0xff;
		sha512_struct->data_out.bytes[i + 16] = (sha512_struct->h2 \
												>> (56 - i * 8)) & 0xff;
		sha512_struct->data_out.bytes[i + 24] = (sha512_struct->h3 \
												>> (56 - i * 8)) & 0xff;
		sha512_struct->data_out.bytes[i + 32] = (sha512_struct->h4 \
												>> (56 - i * 8)) & 0xff;
		sha512_struct->data_out.bytes[i + 40] = (sha512_struct->h5 \
												>> (56 - i * 8)) & 0xff;
		if (command == SHA512)
		{
			sha512_struct->data_out.bytes[i + 48] = (sha512_struct->h6 \
													>> (56 - i * 8)) & 0xff;
			sha512_struct->data_out.bytes[i + 56] = (sha512_struct->h7 \
													>> (56 - i * 8)) & 0xff;
		}
	}
}

void		set_h512(t_sha512 *sha512_struct, enum e_command command)
{
	if (command == SHA512)
	{
		sha512_struct->h0 = (t_uint64)(0x6A09E667F3BCC908);
		sha512_struct->h1 = (t_uint64)(0xBB67AE8584CAA73B);
		sha512_struct->h2 = (t_uint64)(0x3C6EF372FE94F82B);
		sha512_struct->h3 = (t_uint64)(0xA54FF53A5F1D36F1);
		sha512_struct->h4 = (t_uint64)(0x510E527FADE682D1);
		sha512_struct->h5 = (t_uint64)(0x9B05688C2B3E6C1F);
		sha512_struct->h6 = (t_uint64)(0x1F83D9ABFB41BD6B);
		sha512_struct->h7 = (t_uint64)(0x5BE0CD19137E2179);
	}
	else
	{
		sha512_struct->h0 = (t_uint64)(0xCBBB9D5DC1059ED8);
		sha512_struct->h1 = (t_uint64)(0x629A292A367CD507);
		sha512_struct->h2 = (t_uint64)(0x9159015A3070DD17);
		sha512_struct->h3 = (t_uint64)(0x152FECD8F70E5939);
		sha512_struct->h4 = (t_uint64)(0x67332667FFC00B31);
		sha512_struct->h5 = (t_uint64)(0x8EB44A8768581511);
		sha512_struct->h6 = (t_uint64)(0xDB0C2E0D64F98FA7);
		sha512_struct->h7 = (t_uint64)(0x47B5481DBEFA4FA4);
	}
}

void		*set_sha384_512_struct(t_buffer data, enum e_command command)
{
	t_sha512 *sha512_struct;

	sha512_struct = malloc(sizeof(t_sha512));
	if (sha512_struct == NULL)
		error(MALLOC_FAILED, "");
	sha512_struct->k = set_k512(sha512_struct->k);
	sha512_struct->w = malloc(sizeof(t_uint64) * 80);
	if (sha512_struct->w == NULL)
		error(MALLOC_FAILED, "");
	if (command == SHA512)
		sha512_struct->data_out.size = sizeof(t_uint64) * 8;
	else
		sha512_struct->data_out.size = sizeof(t_uint64) * 6;
	sha512_struct->data_out.bytes = malloc(sha512_struct->data_out.size);
	if (sha512_struct->data_out.bytes == NULL)
		error(MALLOC_FAILED, "");
	sha512_struct->data_completed = \
		set_data_completed512(sha512_struct->data_completed, data);
	set_h512(sha512_struct, command);
	return ((void *)sha512_struct);
}
