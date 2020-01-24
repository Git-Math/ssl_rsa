/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 00:36:41 by mnguyen           #+#    #+#             */
/*   Updated: 2019/11/07 00:36:45 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

static t_byte g_base64_table[64] = { 		\
	'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',\
	'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',\
	'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',\
	'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',\
	'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',\
	'o', 'p', 'q', 'r', 's', 't', 'u', 'v',\
	'w', 'x', 'y', 'z', '0', '1', '2', '3',\
	'4', '5', '6', '7', '8', '9', '+', '/' };

t_byte		base64_rev_table(t_byte b)
{
	int i;

	i = 0;
	while (i < 64)
	{
		if (g_base64_table[i] == b)
			return ((t_byte)i);
		i++;
	}
	return ((t_byte)-1);
}

void		base64_encode_last(t_buffer *result, t_buffer *data, int i, int j)
{
	if (data->size - i == 1)
	{
		result->bytes[j] = g_base64_table[(int)(data->bytes[i] >> 2)];
		result->bytes[j + 1] = g_base64_table[(int)((data->bytes[i] & 3) << 4)];
	}
	else if (data->size - i == 2)
	{
		result->bytes[j] = g_base64_table[(int)(data->bytes[i] >> 2)];
		result->bytes[j + 1] = g_base64_table[(int)(((data->bytes[i] & 3) \
			<< 4) | (data->bytes[i + 1] >> 4))];
		result->bytes[j + 2] = g_base64_table[(int)((data->bytes[i + 1] & 15) \
			<< 2)];
	}
}

t_buffer	base64_encode(void *hash_struct)
{
	t_buffer	*data;
	t_buffer	result;
	int			i;
	int			j;

	data = (t_buffer *)hash_struct;
	result.size = (data->size + 2) / 3 * 4;
	result.bytes = malloc(sizeof(t_byte) * result.size);
	(result.bytes == NULL) ? error(MALLOC_FAILED, "") : 0;
	ft_memset(result.bytes, (int)'=', result.size);
	i = 0;
	j = 0;
	while (i < (data->size - data->size % 3))
	{
		result.bytes[j] = g_base64_table[(int)(data->bytes[i] >> 2)];
		result.bytes[j + 1] = g_base64_table[(int)(((data->bytes[i] & 3) \
			<< 4) | (data->bytes[i + 1] >> 4))];
		result.bytes[j + 2] = g_base64_table[(int)(((data->bytes[i + 1] & 15) \
			<< 2) | (data->bytes[i + 2] >> 6))];
		result.bytes[j + 3] = g_base64_table[(int)(data->bytes[i + 2] & 63)];
		j += 4;
		i += 3;
	}
	base64_encode_last(&result, data, i, j);
	return (result);
}

void		base64_decode_last(t_buffer *result, t_buffer *data, int i, int j)
{
	if (data->bytes[data->size - 2] == (t_byte)'=')
	{
		result->bytes[j] = (base64_rev_table(data->bytes[i]) << 2) \
			| (base64_rev_table(data->bytes[i + 1]) >> 4);
	}
	else if (data->bytes[data->size - 1] == (t_byte)'=')
	{
		result->bytes[j] = (base64_rev_table(data->bytes[i]) << 2) \
			| (base64_rev_table(data->bytes[i + 1]) >> 4);
		result->bytes[j + 1] = ((base64_rev_table(data->bytes[i + 1]) & 15) \
			<< 4) | (base64_rev_table(data->bytes[i + 2]) >> 2);
	}
	else
	{
		result->bytes[j] = (base64_rev_table(data->bytes[i]) << 2) \
			| (base64_rev_table(data->bytes[i + 1]) >> 4);
		result->bytes[j + 1] = ((base64_rev_table(data->bytes[i + 1]) & 15) \
			<< 4) | (base64_rev_table(data->bytes[i + 2]) >> 2);
		result->bytes[j + 2] = ((base64_rev_table(data->bytes[i + 2]) & 3) \
			<< 6) | base64_rev_table(data->bytes[i + 3]);
	}
}

t_buffer	base64_decode(void *hash_struct)
{
	t_buffer	*data;
	t_buffer	result;
	int			i;
	int			j;

	result.size = 0;
	data = (t_buffer *)hash_struct;
	if (remove_data_whitespace(data) == NULL)
		return (result);
	base64_decode_init(&result, data);
	i = 0;
	j = 0;
	while (i < data->size - 4)
	{
		result.bytes[j] = (base64_rev_table(data->bytes[i]) << 2) \
			| (base64_rev_table(data->bytes[i + 1]) >> 4);
		result.bytes[j + 1] = ((base64_rev_table(data->bytes[i + 1]) & 15) \
			<< 4) | (base64_rev_table(data->bytes[i + 2]) >> 2);
		result.bytes[j + 2] = ((base64_rev_table(data->bytes[i + 2]) & 3) \
			<< 6) | base64_rev_table(data->bytes[i + 3]);
		j += 3;
		i += 4;
	}
	base64_decode_last(&result, data, i, j);
	return (result);
}
