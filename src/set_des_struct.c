/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_des_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 00:36:27 by mnguyen           #+#    #+#             */
/*   Updated: 2019/11/07 00:36:30 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

t_byte		hex_to_byte(t_args *args, t_byte hex_byte)
{
	if (hex_byte >= '0' && hex_byte <= '9')
		return (hex_byte - '0');
	else if (hex_byte >= 'a' && hex_byte <= 'f')
		return (hex_byte - 'a' + 10);
	else if (hex_byte >= 'A' && hex_byte <= 'F')
		return (hex_byte - 'A' + 10);
	else
		error_free_args(INVALID_HEX, "", args);
	return ('0');
}

t_buffer	buffer_hex_to_byte(t_args *args, t_buffer hex_buf, int size)
{
	t_buffer	byte_buf;
	t_byte		left_part;
	t_byte		right_part;
	int			i;

	byte_buf.size = size;
	byte_buf.bytes = malloc(sizeof(t_byte) * byte_buf.size);
	if (byte_buf.bytes == NULL)
		error(MALLOC_FAILED, "");
	i = 0;
	while (i < byte_buf.size)
	{
		left_part = i * 2 < hex_buf.size ? hex_buf.bytes[i * 2] : '0';
		left_part = hex_to_byte(args, left_part);
		right_part = i * 2 + 1 < hex_buf.size ? hex_buf.bytes[i * 2 + 1] : '0';
		right_part = hex_to_byte(args, right_part);
		byte_buf.bytes[i] = (left_part << 4) | right_part;
		i++;
	}
	return (byte_buf);
}

void		set_des_exclusive(t_args *args, void *hash_struct)
{
	t_des		*des_struct;

	des_struct = (t_des *)hash_struct;
	des_struct->mode = args->command - \
		(args->command >= DES3_ECB ? DES3_ECB : DES_ECB);
	des_struct->encode = args->opts & OPT_D ? FALSE : TRUE;
	des_struct->a = ((args->opts & OPT_A) && args->command < DES3_ECB)\
		? TRUE : FALSE;
	des_struct->a3 = ((args->opts & OPT_A) && args->command >= DES3_ECB)\
		? TRUE : FALSE;
	des_struct->padding = (args->command < DES3_ECB) ? TRUE : FALSE;
	if (args->opts & OPT_K)
		des_struct->key = buffer_hex_to_byte(args, args->key, \
			args->command >= DES3_ECB ? 24 : 8);
	if ((args->opts & OPT_V) && des_struct->mode != ECB)
		des_struct->iv = buffer_hex_to_byte(args, args->iv, 8);
	if (!(args->opts & OPT_K) || (!(args->opts & OPT_V) \
		&& des_struct->mode != ECB))
		pbkdf(args, des_struct);
}

void		*set_des_struct(t_buffer data)
{
	t_des	*des_struct;

	des_struct = malloc(sizeof(t_des));
	if (des_struct == NULL)
		error(MALLOC_FAILED, "");
	des_struct->data = data;
	return ((void *)des_struct);
}

void		free_des_struct(void *hash_struct)
{
	t_des	*des_struct;

	des_struct = (t_des *)hash_struct;
	free(des_struct->key.bytes);
	if (des_struct->mode != ECB)
		free(des_struct->iv.bytes);
	free(des_struct);
}
