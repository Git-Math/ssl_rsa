/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha512.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:39:27 by mnguyen           #+#    #+#             */
/*   Updated: 2019/01/14 17:24:12 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_md5.h"

t_uint64	right_rotate_long(t_uint64 value, t_uint64 offset)
{
	return (((value) >> (offset)) | ((value) << (64 - (offset))));
}

void		free_sha512_struct(void *hash_struct)
{
	t_sha512 *sha512_struct;

	sha512_struct = (t_sha512 *)hash_struct;
	free(sha512_struct->data_completed.bytes);
	free(sha512_struct->k);
	free(sha512_struct->w);
	free(sha512_struct);
}

void		sha5121(t_sha512 *sha512_struct, int i)
{
	sha512_struct->t1 = sha512_struct->h		   \
		+ (right_rotate_long(sha512_struct->e, 14) \
		^ right_rotate_long(sha512_struct->e, 18)  \
		^ right_rotate_long(sha512_struct->e, 41)) \
		+ (sha512_struct->g ^ (sha512_struct->e	   \
		& (sha512_struct->f ^ sha512_struct->g)))  \
		+ sha512_struct->k[i] + sha512_struct->w[i];
	sha512_struct->t2 = (right_rotate_long(sha512_struct->a, 28) \
		^ right_rotate_long(sha512_struct->a, 34)				 \
		^ right_rotate_long(sha512_struct->a, 39))				 \
		+ ((sha512_struct->a & sha512_struct->b)				 \
		| (sha512_struct->c & (sha512_struct->a					 \
		| sha512_struct->b)));
	sha512_struct->h = sha512_struct->g;
	sha512_struct->g = sha512_struct->f;
	sha512_struct->f = sha512_struct->e;
	sha512_struct->e = sha512_struct->d + sha512_struct->t1;
	sha512_struct->d = sha512_struct->c;
	sha512_struct->c = sha512_struct->b;
	sha512_struct->b = sha512_struct->a;
	sha512_struct->a = sha512_struct->t1 + sha512_struct->t2;
}

void		sha5120(t_sha512 *sha512_struct)
{
	int i;

	sha512_struct->a = sha512_struct->h0;
	sha512_struct->b = sha512_struct->h1;
	sha512_struct->c = sha512_struct->h2;
	sha512_struct->d = sha512_struct->h3;
	sha512_struct->e = sha512_struct->h4;
	sha512_struct->f = sha512_struct->h5;
	sha512_struct->g = sha512_struct->h6;
	sha512_struct->h = sha512_struct->h7;
	i = 0;
	while (i < 80)
	{
		sha5121(sha512_struct, i);
		i++;
	}
	sha512_struct->h0 += sha512_struct->a;
	sha512_struct->h1 += sha512_struct->b;
	sha512_struct->h2 += sha512_struct->c;
	sha512_struct->h3 += sha512_struct->d;
	sha512_struct->h4 += sha512_struct->e;
	sha512_struct->h5 += sha512_struct->f;
	sha512_struct->h6 += sha512_struct->g;
	sha512_struct->h7 += sha512_struct->h;
}

t_buffer	sha384_512(void *hash_struct, enum e_command command)
{
	int			i;
	t_sha512	*sha512_struct;

	sha512_struct = (t_sha512 *)hash_struct;
	i = 0;
	while (i < sha512_struct->data_completed.size)
	{
		set_w512(sha512_struct, i);
		sha5120(sha512_struct);
		i += 128;
	}
	set_data_out512(sha512_struct, command);
	return (sha512_struct->data_out);
}
