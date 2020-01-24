/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 00:36:59 by mnguyen           #+#    #+#             */
/*   Updated: 2019/11/07 00:37:01 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

void		des_initialize(t_des *des_struct, t_buffer *result)
{
	des_struct->data = data_setup(des_struct);
	des_struct->key_array = des_key_setup(des_struct->key);
	des_struct->data_array = (t_buffer *)malloc(sizeof(t_buffer) * 17);
	result->size = des_struct->data.size;
	result->bytes = (t_byte *)malloc(sizeof(t_byte) * result->size);
	if (des_struct->data_array == NULL || result->bytes == NULL)
		error(MALLOC_FAILED, "");
	des_struct->i = 0;
	while (des_struct->i < 17)
	{
		des_struct->data_array[des_struct->i].size = 8;
		des_struct->data_array[des_struct->i].bytes = (t_byte *)malloc(\
			sizeof(t_byte) * des_struct->data_array[des_struct->i].size);
		if (des_struct->data_array[des_struct->i].bytes == NULL)
			error(MALLOC_FAILED, "");
		des_struct->i++;
	}
}

void		des_finalize(t_des *des_struct, t_buffer *result)
{
	*result = result_finalize(*result, des_struct);
	des_struct->i = 0;
	while (des_struct->i < 17)
	{
		free(des_struct->data_array[des_struct->i].bytes);
		if (des_struct->i < 16)
			free(des_struct->key_array[des_struct->i].bytes);
		des_struct->i++;
	}
	if ((des_struct->encode && des_struct->padding && des_struct->mode < CFB) \
		|| (!des_struct->encode && des_struct->a))
		free(des_struct->data.bytes);
	free(des_struct->data_array);
	free(des_struct->key_array);
}

void		des_compute(t_des *des_struct)
{
	ft_memcpy(des_struct->data_array[des_struct->j + 1].bytes, \
		des_struct->data_array[des_struct->j].bytes + 4, 4);
	ft_memcpy(des_struct->data_array[des_struct->j + 1].bytes + 4, \
		des_struct->data_array[des_struct->j].bytes, 4);
	des_struct->f_result = f(des_struct->data_array, \
		des_struct->key_array, des_struct->j, des_struct);
	des_xor(des_struct->data_array[des_struct->j + 1].bytes + 4, \
		des_struct->f_result.bytes, 4);
	free(des_struct->f_result.bytes);
}

t_buffer	des(void *hash_struct)
{
	t_des		*des_struct;
	t_buffer	result;

	des_struct = (t_des *)hash_struct;
	des_initialize(des_struct, &result);
	des_struct->i = 0;
	while (des_struct->i < des_struct->data.size)
	{
		des_ip(des_struct, &result);
		des_struct->j = 0;
		while (des_struct->j < 16)
		{
			des_compute(des_struct);
			des_struct->j++;
		}
		des_fp(des_struct, &result);
		free(des_struct->block_result.bytes);
		des_struct->i += 8;
	}
	des_finalize(des_struct, &result);
	return (result);
}
