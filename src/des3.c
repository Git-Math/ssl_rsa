/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 00:37:09 by mnguyen           #+#    #+#             */
/*   Updated: 2019/11/07 00:37:12 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

t_buffer	default_data(t_des *des_struct)
{
	t_buffer	data_result;

	data_result.size = des_struct->data.size;
	data_result.bytes = malloc(sizeof(t_byte) * data_result.size);
	ft_memcpy(data_result.bytes, des_struct->data.bytes, data_result.size);
	return (data_result);
}

t_buffer	des3_data_setup(t_des *des_struct)
{
	t_buffer	data_result;
	int			padding;
	int			i;

	if (des_struct->encode && des_struct->mode < CFB)
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
	else if (!des_struct->encode && des_struct->a3)
	{
		data_result = base64_decode((void *)&des_struct->data);
		(data_result.size == 0) ? error(INVALID_INPUT, "DES: BASE64") : 0;
		return (data_result);
	}
	else
		return (default_data(des_struct));
}

t_buffer	des3_result_finalize(t_buffer result, t_des *des_struct)
{
	t_buffer	prev_result;
	int			padding;
	int			i;

	if (!des_struct->encode && des_struct->mode < CFB)
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
	else if (des_struct->encode && des_struct->a3)
	{
		prev_result = result;
		result = base64_encode((void *)&prev_result);
		free(prev_result.bytes);
	}
	return (result);
}

void		des3_compute(t_des *des_struct, t_buffer *result, t_buffer data,\
	int i)
{
	des_struct->data.size = ((i + 8) <= data.size) ? 8 : data.size % 8;
	ft_memcpy(des_struct->data.bytes, data.bytes + i,\
		des_struct->data.size);
	if (!des_struct->encode)
		des_struct->key.bytes += 16;
	*result = des((void *)des_struct);
	ft_memcpy(des_struct->data.bytes, result->bytes, result->size);
	free(result->bytes);
	des_struct->encode = des_struct->encode ? FALSE : TRUE;
	des_struct->key.bytes += des_struct->encode ? -8 : 8;
	*result = des((void *)des_struct);
	ft_memcpy(des_struct->data.bytes, result->bytes, result->size);
	free(result->bytes);
	des_struct->encode = des_struct->encode ? FALSE : TRUE;
	des_struct->key.bytes += des_struct->encode ? 8 : -8;
	*result = des((void *)des_struct);
	des_struct->key.bytes += des_struct->encode ? -16 : 0;
}

t_buffer	des3(void *hash_struct)
{
	t_des		*des_struct;
	t_buffer	data;
	t_buffer	final_result;
	t_buffer	result;
	int			i;

	des_struct = (t_des *)hash_struct;
	data = des3_data_setup(des_struct);
	final_result.bytes = malloc(sizeof(t_byte) * data.size);
	final_result.size = 0;
	i = 0;
	while (i < data.size)
	{
		if (i > 0 && des_struct->mode != ECB && des_struct->encode)
			ft_memcpy(des_struct->iv.bytes, final_result.bytes + i - 8, 8);
		else if (i > 0 && des_struct->mode != ECB && !des_struct->encode)
			ft_memcpy(des_struct->iv.bytes, data.bytes + i - 8, 8);
		des3_compute(des_struct, &result, data, i);
		final_result.size += result.size;
		ft_memcpy(final_result.bytes + i, result.bytes, result.size);
		free(result.bytes);
		i += 8;
	}
	free(data.bytes);
	return (des3_result_finalize(final_result, des_struct));
}
