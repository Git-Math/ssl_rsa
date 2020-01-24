/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_binary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 19:40:01 by mnguyen           #+#    #+#             */
/*   Updated: 2019/11/08 19:40:03 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

t_buffer	des_permutation(t_byte *data, int *table, int table_size)
{
	int			i;
	t_buffer	result;

	result.size = table_size / 8;
	result.bytes = (t_byte *)malloc(sizeof(t_byte) * result.size);
	if (result.bytes == NULL)
		error(MALLOC_FAILED, "");
	result.bytes = ft_memset(result.bytes, 0, result.size);
	i = 0;
	while (i < table_size)
	{
		result.bytes[i / 8] |= ((data[(table[i] - 1) / 8] \
			>> (7 - ((table[i] - 1) % 8))) & 1) << (7 - i % 8);
		i++;
	}
	return (result);
}

t_buffer	des_left_rotate(t_buffer key, int shift_nb)
{
	int			i;
	t_buffer	result;

	result.size = 7;
	result.bytes = (t_byte *)malloc(sizeof(t_byte) * result.size);
	if (result.bytes == NULL)
		error(MALLOC_FAILED, "");
	result.bytes = ft_memset(result.bytes, 0, result.size);
	i = 0;
	while (i < key.size * 8)
	{
		if (i < 28 && (i + shift_nb) >= 28)
			result.bytes[i / 8] |= ((key.bytes[0] \
				>> (7 - (i + shift_nb - 28))) & 1) << (7 - i % 8);
		else if ((i + shift_nb) >= 56)
			result.bytes[i / 8] |= ((key.bytes[3] \
				>> (7 - (i + shift_nb - 56 + 4))) & 1) << (7 - i % 8);
		else
			result.bytes[i / 8] |= ((key.bytes[(i + shift_nb) / 8] \
				>> (7 - (i % 8 + shift_nb) % 8)) & 1) << (7 - i % 8);
		i++;
	}
	return (result);
}

void		des_xor(t_byte *dest, t_byte *other, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		dest[i] ^= other[i];
		i++;
	}
}

void		des_reverse(t_buffer buff)
{
	int		i;
	t_byte	tmp;

	i = 0;
	while (i < 4)
	{
		tmp = buff.bytes[i];
		buff.bytes[i] = buff.bytes[i + 4];
		buff.bytes[i + 4] = tmp;
		i++;
	}
}
