/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 19:24:34 by mnguyen           #+#    #+#             */
/*   Updated: 2019/01/14 17:19:58 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_md5.h"

t_uint32	left_rotate(t_uint32 value, t_uint32 offset)
{
	return (((value) << (offset)) | ((value) >> (32 - (offset))));
}

void		free_md5_struct(void *hash_struct)
{
	t_md5 *md5_struct;

	md5_struct = (t_md5 *)hash_struct;
	free(md5_struct->data_completed.bytes);
	free(md5_struct->r);
	free(md5_struct->s);
	free(md5_struct);
}

void		md51(t_md5 *md5_struct, int i)
{
	if (i < 16)
	{
		md5_struct->f = (md5_struct->b & md5_struct->c) \
			| ((~md5_struct->b) & md5_struct->d);
		md5_struct->g = i;
	}
	else if (i < 32)
	{
		md5_struct->f = (md5_struct->d & md5_struct->b) \
			| ((~md5_struct->d) & md5_struct->c);
		md5_struct->g = (5 * i + 1) % 16;
	}
	else if (i < 48)
	{
		md5_struct->f = md5_struct->b ^ md5_struct->c ^ md5_struct->d;
		md5_struct->g = (3 * i + 5) % 16;
	}
	else
	{
		md5_struct->f = md5_struct->c ^ (md5_struct->b | (~md5_struct->d));
		md5_struct->g = (7 * i) % 16;
	}
}

void		md50(t_md5 *md5_struct)
{
	int i;

	md5_struct->a = md5_struct->h0;
	md5_struct->b = md5_struct->h1;
	md5_struct->c = md5_struct->h2;
	md5_struct->d = md5_struct->h3;
	i = 0;
	while (i < 64)
	{
		md51(md5_struct, i);
		md5_struct->tmp = md5_struct->d;
		md5_struct->d = md5_struct->c;
		md5_struct->c = md5_struct->b;
		md5_struct->b += left_rotate(md5_struct->a + md5_struct->f	\
									+ md5_struct->s[i]				\
									+ md5_struct->w[md5_struct->g]	\
									, md5_struct->r[i]);
		md5_struct->a = md5_struct->tmp;
		i++;
	}
	md5_struct->h0 += md5_struct->a;
	md5_struct->h1 += md5_struct->b;
	md5_struct->h2 += md5_struct->c;
	md5_struct->h3 += md5_struct->d;
}

t_buffer	md5(void *hash_struct)
{
	int			i;
	t_md5		*md5_struct;

	md5_struct = (t_md5 *)hash_struct;
	i = 0;
	while (i < md5_struct->data_completed.size)
	{
		md5_struct->w = (t_uint32 *)(md5_struct->data_completed.bytes + i);
		md50(md5_struct);
		i += 64;
	}
	ft_memcpy(md5_struct->data_out.bytes, &md5_struct->h0, 4);
	ft_memcpy(md5_struct->data_out.bytes + 4, &md5_struct->h1, 4);
	ft_memcpy(md5_struct->data_out.bytes + 8, &md5_struct->h2, 4);
	ft_memcpy(md5_struct->data_out.bytes + 12, &md5_struct->h3, 4);
	return (md5_struct->data_out);
}
