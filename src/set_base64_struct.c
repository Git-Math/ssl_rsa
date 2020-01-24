/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_base64_struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 00:39:03 by mnguyen           #+#    #+#             */
/*   Updated: 2019/11/07 00:39:06 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

t_buffer	*remove_data_whitespace0(t_buffer *data, int *equal_count, \
	int *j, int i)
{
	if ((data->bytes[i] >= 'A' && data->bytes[i] <= 'Z')	\
		|| (data->bytes[i] >= 'a' && data->bytes[i] <= 'z')	\
		|| (data->bytes[i] >= '0' && data->bytes[i] <= '9') \
		|| data->bytes[i] == '+' || data->bytes[i] == '/' \
		|| data->bytes[i] == '=')
	{
		if (data->bytes[i] == '=' && *equal_count >= 2)
			return (NULL);
		else if (data->bytes[i] == '=')
			(*equal_count)++;
		else if (*equal_count > 0)
			return (NULL);
		data->bytes[*j] = data->bytes[i];
		(*j)++;
	}
	else if (data->bytes[i] != ' ' && data->bytes[i] != '\n' \
		&& data->bytes[i] != '\r' \
		&& data->bytes[i] != '\t' && data->bytes[i] != '\v' \
		&& data->bytes[i] != '\f')
		return (NULL);
	return (data);
}

t_buffer	*remove_data_whitespace(t_buffer *data)
{
	int i;
	int j;
	int equal_count;

	i = 0;
	j = 0;
	equal_count = 0;
	while (i < data->size)
	{
		if (remove_data_whitespace0(data, &equal_count, &j, i) == NULL)
			return (NULL);
		i++;
	}
	data->size = j;
	if (data->size == 0 || data->size % 4 != 0)
		return (NULL);
	return (data);
}

void		*set_base64_struct(t_buffer data)
{
	t_buffer *base64_struct;

	base64_struct = malloc(sizeof(t_buffer));
	if (base64_struct == NULL)
		error(MALLOC_FAILED, "");
	base64_struct->bytes = data.bytes;
	base64_struct->size = data.size;
	return ((void *)base64_struct);
}

void		free_base64_struct(void *hash_struct)
{
	t_buffer *base64_struct;

	base64_struct = (t_buffer *)hash_struct;
	free(base64_struct);
}
