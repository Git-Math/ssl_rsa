/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 19:39:42 by mnguyen           #+#    #+#             */
/*   Updated: 2019/11/08 19:39:46 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

static int g_des_e_table[48] = { 32, 1, 2, 3, 4, 5,\
	4, 5, 6, 7, 8, 9,\
	8, 9, 10, 11, 12, 13,\
	12, 13, 14, 15, 16, 17,\
	16, 17, 18, 19, 20, 21,\
	20, 21, 22, 23, 24, 25,\
	24, 25, 26, 27, 28, 29,\
	28, 29, 30, 31, 32, 1 };

static int g_des_p_table[32] = { 16, 7, 20, 21,\
	29, 12, 28, 17,\
	1, 15, 23, 26,\
	5, 18, 31, 10,\
	2, 8, 24, 14,\
	32, 27, 3, 9,\
	19, 13, 30, 6,\
	22, 11, 4, 25 };

static int g_s1[64] = { \
	14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,\
	0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,\
	4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,\
	15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 };

static int g_s2[64] = { \
	15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,\
	3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,\
	0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,\
	13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 };

static int g_s3[64] = { \
	10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,\
	13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,\
	13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,\
	1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 };

static int g_s4[64] = { \
	7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,\
	13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,\
	10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,\
	3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 };

static int g_s5[64] = { \
	2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,\
	14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,\
	4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,\
	11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 };

static int g_s6[64] = { \
	12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,\
	10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,\
	9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,\
	4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 };

static int g_s7[64] = { \
	4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,\
	13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,\
	1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,\
	6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 };

static int g_s8[64] = { \
	13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,\
	1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,\
	7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,\
	2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 };

static int g_des_shifts[16] = { 1, 1, 2, 2, 2, 2, 2, 2,\
	1, 2, 2, 2, 2, 2, 2, 1 };

static int g_des_pc1_table[56] = { 57, 49, 41, 33, 25, 17, 9,\
	1, 58, 50, 42, 34, 26, 18,\
	10, 2, 59, 51, 43, 35, 27,\
	19, 11, 3, 60, 52, 44, 36,\
	63, 55, 47, 39, 31, 23, 15,\
	7, 62, 54, 46, 38, 30, 22,\
	14, 6, 61, 53, 45, 37, 29,\
	21, 13, 5, 28, 20, 12, 4 };

static int g_des_pc2_table[48] = { 14, 17, 11, 24, 1, 5,\
	3, 28, 15, 6, 21, 10,\
	23, 19, 12, 4, 26, 8,\
	16, 7, 27, 20, 13, 2,\
	41, 52, 31, 37, 47, 55,\
	30, 40, 51, 45, 33, 48,\
	44, 49, 39, 56, 34, 53,\
	46, 42, 50, 36, 29, 32 };

t_buffer	*des_key_setup(t_buffer key)
{
	t_buffer	*key_shift_array;
	t_buffer	*key_array;
	int			i;

	key_shift_array = (t_buffer *)malloc(sizeof(t_buffer) * 17);
	key_array = (t_buffer *)malloc(sizeof(t_buffer) * 16);
	if (key_shift_array == NULL || key_array == NULL)
		error(MALLOC_FAILED, "");
	key_shift_array[0] = des_permutation(key.bytes, g_des_pc1_table, 56);
	i = 0;
	while (i < 16)
	{
		key_shift_array[i + 1] = \
			des_left_rotate(key_shift_array[i], g_des_shifts[i]);
		key_array[i] = \
			des_permutation(key_shift_array[i + 1].bytes, g_des_pc2_table, 48);
		free(key_shift_array[i].bytes);
		i++;
	}
	free(key_shift_array[i].bytes);
	free(key_shift_array);
	return (key_array);
}

void		f_set_s(t_buffer *s, t_buffer e)
{
	s->bytes[0] = (t_byte)(g_s1[(e.bytes[0] >> 2 & 0x20) \
		| (e.bytes[0] << 2 & 0x10) | (e.bytes[0] >> 3 & 0xf)] << 4) \
		| (t_byte)g_s2[(e.bytes[0] << 4 & 0x20) | (e.bytes[1] & 0x10) \
		| (e.bytes[0] << 3 & 0x8) | (e.bytes[1] >> 5 & 0x7)];
	s->bytes[1] = (t_byte)(g_s3[(e.bytes[1] << 2 & 0x20) \
		| (e.bytes[2] >> 2 & 0x10) | (e.bytes[1] << 1 & 0xe) \
		| (e.bytes[2] >> 7 & 0x1)] << 4) | (t_byte)g_s4[(e.bytes[2] & 0x20) \
		| (e.bytes[2] << 4 & 0x10) | (e.bytes[2] >> 1 & 0xf)];
	s->bytes[2] = (t_byte)(g_s5[(e.bytes[3] >> 2 & 0x20) \
		| (e.bytes[3] << 2 & 0x10) | (e.bytes[3] >> 3 & 0xf)] << 4) \
		| (t_byte)g_s6[(e.bytes[3] << 4 & 0x20) | (e.bytes[4] & 0x10) \
		| (e.bytes[3] << 3 & 0x8) | (e.bytes[4] >> 5 & 0x7)];
	s->bytes[3] = (t_byte)(g_s7[(e.bytes[4] << 2 & 0x20) \
		| (e.bytes[5] >> 2 & 0x10) | (e.bytes[4] << 1 & 0xe) \
		| (e.bytes[5] >> 7 & 0x1)] << 4) | (t_byte)g_s8[(e.bytes[5] & 0x20) \
		| (e.bytes[5] << 4 & 0x10) | (e.bytes[5] >> 1 & 0xf)];
}

t_buffer	f(t_buffer *data_array, t_buffer *key_array, \
	int j, t_des *des_struct)
{
	t_buffer	e;
	t_buffer	s;
	t_buffer	result;

	e = des_permutation(data_array[j].bytes + 4, g_des_e_table, 48);
	des_xor(e.bytes, key_array[(des_struct->encode \
		|| des_struct->mode >= CFB) ? j : 15 - j].bytes, 6);
	s.size = 4;
	s.bytes = (t_byte *)malloc(sizeof(t_byte) * s.size);
	if (s.bytes == NULL)
		error(MALLOC_FAILED, "");
	f_set_s(&s, e);
	free(e.bytes);
	result = des_permutation(s.bytes, g_des_p_table, 32);
	free(s.bytes);
	return (result);
}

t_buffer	data_setup(t_des *des_struct)
{
	t_buffer	data_result;
	int			padding;
	int			i;

	if (des_struct->encode && des_struct->padding && des_struct->mode < CFB)
	{
		padding = 1 + ((8 - ((des_struct->data.size + 1) % 8)) % 8);
		data_result.size = des_struct->data.size + padding;
		data_result.bytes = malloc(sizeof(t_byte) * data_result.size);
		(data_result.bytes == NULL) ? error(MALLOC_FAILED, "") : 0;
		ft_memcpy(data_result.bytes, des_struct->data.bytes, \
			des_struct->data.size);
		i = des_struct->data.size;
		while (i < data_result.size)
			data_result.bytes[i++] = (t_byte)padding;
		return (data_result);
	}
	else if (!des_struct->encode && des_struct->a)
	{
		data_result = base64_decode((void *)&des_struct->data);
		if (data_result.size == 0)
			error(INVALID_INPUT, "DES: BASE64");
		return (data_result);
	}
	return (des_struct->data);
}

t_buffer	result_finalize(t_buffer result, t_des *des_struct)
{
	t_buffer	prev_result;
	int			padding;
	int			i;

	if (!des_struct->encode && des_struct->padding && des_struct->mode < CFB)
	{
		(result.size < 8) ? error(INVALID_INPUT, "DES") : 0;
		padding = (int)result.bytes[result.size - 1];
		(padding < 1 || padding > 8) ? error(INVALID_INPUT, "DES") : 0;
		i = 0;
		while (i < padding)
		{
			if ((int)result.bytes[result.size - 1 - i] != padding)
				error(INVALID_INPUT, "DES");
			i++;
		}
		result.size -= padding;
	}
	else if (des_struct->encode && des_struct->a)
	{
		prev_result = result;
		result = base64_encode((void *)&prev_result);
		free(prev_result.bytes);
	}
	return (result);
}
