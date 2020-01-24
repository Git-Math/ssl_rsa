/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_ifp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 20:03:16 by mnguyen           #+#    #+#             */
/*   Updated: 2019/11/08 20:03:25 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

static int g_des_ip_table[64] = { 58, 50, 42, 34, 26, 18, 10, 2,\
	60, 52, 44, 36, 28, 20, 12, 4,\
	62, 54, 46, 38, 30, 22, 14, 6,\
	64, 56, 48, 40, 32, 24, 16, 8,\
	57, 49, 41, 33, 25, 17, 9, 1,\
	59, 51, 43, 35, 27, 19, 11, 3,\
	61, 53, 45, 37, 29, 21, 13, 5,\
	63, 55, 47, 39, 31, 23, 15, 7 };

static int g_des_fp_table[64] = { 40, 8, 48, 16, 56, 24, 64, 32,\
	39, 7, 47, 15, 55, 23, 63, 31,\
	38, 6, 46, 14, 54, 22, 62, 30,\
	37, 5, 45, 13, 53, 21, 61, 29,\
	36, 4, 44, 12, 52, 20, 60, 28,\
	35, 3, 43, 11, 51, 19, 59, 27,\
	34, 2, 42, 10, 50, 18, 58, 26,\
	33, 1, 41, 9, 49, 17, 57, 25 };

void		des_ip(t_des *des_struct, t_buffer *result)
{
	if (des_struct->mode <= CBC \
		|| (des_struct->mode == PCBC && !des_struct->encode))
		des_struct->input_bytes = des_struct->data.bytes + des_struct->i;
	else if (des_struct->mode >= PCBC && des_struct->i == 0)
		des_struct->input_bytes = des_struct->iv.bytes;
	else if (des_struct->mode == PCBC)
		des_struct->input_bytes = des_struct->data.bytes + des_struct->i - 8;
	else if (des_struct->mode == CFB)
		des_struct->input_bytes = (des_struct->encode ? result->bytes \
			+ des_struct->i - 8 : des_struct->data.bytes + des_struct->i - 8);
	if (des_struct->mode == CBC && des_struct->encode)
		des_xor(des_struct->input_bytes, (des_struct->i == 0 ? \
			des_struct->iv.bytes : result->bytes + des_struct->i - 8), 8);
	else if (des_struct->mode == PCBC && des_struct->encode \
		&& des_struct->i == 0)
		des_xor(des_struct->input_bytes, des_struct->data.bytes, 8);
	else if (des_struct->mode == PCBC && des_struct->encode)
	{
		des_xor(des_struct->input_bytes, result->bytes + des_struct->i - 8, 8);
		des_xor(des_struct->input_bytes, des_struct->data.bytes \
			+ des_struct->i, 8);
	}
	free(des_struct->data_array[0].bytes);
	des_struct->data_array[0] = des_permutation(des_struct->input_bytes, \
		g_des_ip_table, 64);
}

void		des_fp_mode(t_des *des_struct, t_buffer *result)
{
	if (des_struct->mode == OFB)
	{
		if (des_struct->i == 0)
		{
			des_struct->input_bytes = (t_byte *)malloc(sizeof(t_byte) * 8);
			if (des_struct->data_array[des_struct->i].bytes == NULL)
				error(MALLOC_FAILED, "");
		}
		ft_memcpy(des_struct->input_bytes, des_struct->block_result.bytes, 8);
		if (des_struct->i + 8 >= des_struct->data.size)
			free(des_struct->input_bytes);
	}
	if ((des_struct->mode == CBC || des_struct->mode == PCBC) \
		&& !des_struct->encode)
		des_xor(des_struct->block_result.bytes, (des_struct->i == 0 ? \
			des_struct->iv.bytes : des_struct->data.bytes \
			+ des_struct->i - 8), 8);
	if (des_struct->mode == PCBC && !des_struct->encode && des_struct->i != 0)
		des_xor(des_struct->block_result.bytes, \
			result->bytes + des_struct->i - 8, 8);
	if (des_struct->mode >= CFB)
		des_xor(des_struct->block_result.bytes, des_struct->data.bytes \
			+ des_struct->i, (des_struct->i + 8) \
			<= des_struct->data.size ? 8 : (des_struct->data.size % 8));
}

void		des_fp(t_des *des_struct, t_buffer *result)
{
	des_reverse(des_struct->data_array[des_struct->j]);
	des_struct->block_result = des_permutation(\
		des_struct->data_array[des_struct->j].bytes, g_des_fp_table, 64);
	des_fp_mode(des_struct, result);
	ft_memcpy(result->bytes + des_struct->i, \
		des_struct->block_result.bytes, (des_struct->i + 8) \
		<= des_struct->data.size ? 8 : (des_struct->data.size % 8));
}
