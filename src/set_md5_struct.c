/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_md5_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:13:37 by mnguyen           #+#    #+#             */
/*   Updated: 2019/01/14 17:21:57 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_md5.h"

t_buffer	set_data_completed(t_buffer data_completed \
									, t_buffer data, t_bool is_little_endian)
{
	size_t b;
	size_t rb;

	data_completed.size = data.size + 9 + (64 - (data.size + 9) % 64) % 64;
	data_completed.bytes = malloc(data_completed.size);
	if (data_completed.bytes == NULL)
		error(MALLOC_FAILED, "");
	data_completed.bytes = ft_memset(data_completed.bytes \
									, 0, data_completed.size);
	data_completed.bytes = ft_memcpy(data_completed.bytes \
									, data.bytes, data.size);
	data_completed.bytes[data.size] = 1 << 7;
	b = data.size * 8;
	if (is_little_endian)
		ft_memcpy(data_completed.bytes + data_completed.size - 8, &b, 8);
	else
	{
		rb = ((b << 56) & 0xff00000000000000) | ((b << 40) & 0xff000000000000) \
			| ((b << 24) & 0xff0000000000) | ((b << 8) & 0xff00000000)		   \
			| ((b >> 8) & 0xff000000) | ((b >> 24) & 0xff0000)				   \
			| ((b >> 40) & 0xff00) | ((b >> 56) & 0xff);
		ft_memcpy(data_completed.bytes + data_completed.size - 8, &rb, 8);
	}
	return (data_completed);
}

void		set_r0(t_uint32 *r, int i)
{
	if (i < 16)
	{
		r[i] = 7;
		r[i + 1] = 12;
		r[i + 2] = 17;
		r[i + 3] = 22;
	}
	else if (i < 32)
	{
		r[i] = 5;
		r[i + 1] = 9;
		r[i + 2] = 14;
		r[i + 3] = 20;
	}
	else
	{
		r[i] = 4;
		r[i + 1] = 11;
		r[i + 2] = 16;
		r[i + 3] = 23;
	}
}

t_uint32	*set_r(t_uint32 *r)
{
	int i;

	r = malloc(sizeof(t_uint32) * 64);
	if (r == NULL)
		error(MALLOC_FAILED, "");
	i = 0;
	while (i < 64)
	{
		if (i < 48)
			set_r0(r, i);
		else
		{
			r[i] = 6;
			r[i + 1] = 10;
			r[i + 2] = 15;
			r[i + 3] = 21;
		}
		i += 4;
	}
	return (r);
}

void		*set_md5_struct(t_buffer data)
{
	t_md5 *md5_struct;

	md5_struct = malloc(sizeof(t_md5));
	if (md5_struct == NULL)
		error(MALLOC_FAILED, "");
	md5_struct->r = set_r(md5_struct->r);
	md5_struct->s = set_s(md5_struct->s);
	md5_struct->data_out.size = sizeof(int) * 4;
	md5_struct->data_out.bytes = malloc(md5_struct->data_out.size);
	if (md5_struct->data_out.bytes == NULL)
		error(MALLOC_FAILED, "");
	md5_struct->data_completed = set_data_completed(md5_struct->data_completed \
													, data, TRUE);
	md5_struct->h0 = 0x67452301;
	md5_struct->h1 = 0xEFCDAB89;
	md5_struct->h2 = 0x98BADCFE;
	md5_struct->h3 = 0x10325476;
	return ((void *)md5_struct);
}
