/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base640.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 02:39:33 by mnguyen           #+#    #+#             */
/*   Updated: 2019/11/07 02:39:37 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

void	base64_decode_init(t_buffer *result, t_buffer *data)
{
	result->size = data->size / 4 * 3;
	if (data->bytes[data->size - 2] == (t_byte)('='))
		result->size -= 2;
	else if (data->bytes[data->size - 1] == (t_byte)('='))
		result->size -= 1;
	result->bytes = malloc(sizeof(t_byte) * result->size);
	if (result->bytes == NULL)
		error(MALLOC_FAILED, "");
}
