/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:27:47 by mnguyen           #+#    #+#             */
/*   Updated: 2019/01/14 17:22:31 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_md5.h"

t_uint32	right_rotate(t_uint32 value, t_uint32 offset)
{
	return (((value) >> (offset)) | ((value) << (32 - (offset))));
}

void		free_sha256_struct(void *hash_struct)
{
	t_sha256 *sha256_struct;

	sha256_struct = (t_sha256 *)hash_struct;
	free(sha256_struct->data_completed.bytes);
	free(sha256_struct->k);
	free(sha256_struct->w);
	free(sha256_struct);
}

void		sha2561(t_sha256 *sha256_struct, int i)
{
	sha256_struct->t1 = sha256_struct->h		  \
		+ (right_rotate(sha256_struct->e, 6)	  \
		^ right_rotate(sha256_struct->e, 11)	  \
		^ right_rotate(sha256_struct->e, 25))	  \
		+ ((sha256_struct->e & sha256_struct->f)  \
		^ (~sha256_struct->e & sha256_struct->g)) \
		+ sha256_struct->k[i] + sha256_struct->w[i];
	sha256_struct->t2 = (right_rotate(sha256_struct->a, 2) \
		^ right_rotate(sha256_struct->a, 13)			   \
		^ right_rotate(sha256_struct->a, 22))			   \
		+ ((sha256_struct->a & sha256_struct->b)		   \
		^ (sha256_struct->a & sha256_struct->c)			   \
		^ (sha256_struct->b & sha256_struct->c));
	sha256_struct->h = sha256_struct->g;
	sha256_struct->g = sha256_struct->f;
	sha256_struct->f = sha256_struct->e;
	sha256_struct->e = sha256_struct->d + sha256_struct->t1;
	sha256_struct->d = sha256_struct->c;
	sha256_struct->c = sha256_struct->b;
	sha256_struct->b = sha256_struct->a;
	sha256_struct->a = sha256_struct->t1 + sha256_struct->t2;
}

void		sha2560(t_sha256 *sha256_struct)
{
	int i;

	sha256_struct->a = sha256_struct->h0;
	sha256_struct->b = sha256_struct->h1;
	sha256_struct->c = sha256_struct->h2;
	sha256_struct->d = sha256_struct->h3;
	sha256_struct->e = sha256_struct->h4;
	sha256_struct->f = sha256_struct->h5;
	sha256_struct->g = sha256_struct->h6;
	sha256_struct->h = sha256_struct->h7;
	i = 0;
	while (i < 64)
	{
		sha2561(sha256_struct, i);
		i++;
	}
	sha256_struct->h0 += sha256_struct->a;
	sha256_struct->h1 += sha256_struct->b;
	sha256_struct->h2 += sha256_struct->c;
	sha256_struct->h3 += sha256_struct->d;
	sha256_struct->h4 += sha256_struct->e;
	sha256_struct->h5 += sha256_struct->f;
	sha256_struct->h6 += sha256_struct->g;
	sha256_struct->h7 += sha256_struct->h;
}

t_buffer	sha224_256(void *hash_struct, enum e_command command)
{
	int				i;
	t_sha256		*sha256_struct;

	sha256_struct = (t_sha256 *)hash_struct;
	i = 0;
	while (i < sha256_struct->data_completed.size)
	{
		set_w(sha256_struct, i);
		sha2560(sha256_struct);
		i += 64;
	}
	set_data_out(sha256_struct, command);
	return (sha256_struct->data_out);
}
