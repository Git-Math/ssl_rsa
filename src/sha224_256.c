/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224_256.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:20:20 by mnguyen           #+#    #+#             */
/*   Updated: 2019/01/14 15:20:36 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_md5.h"

void		*set_sha224_struct(t_buffer data)
{
	return (set_sha224_256_struct(data, SHA224));
}

void		*set_sha256_struct(t_buffer data)
{
	return (set_sha224_256_struct(data, SHA256));
}

t_buffer	sha224(void *hash_struct)
{
	return (sha224_256(hash_struct, SHA224));
}

t_buffer	sha256(void *hash_struct)
{
	return (sha224_256(hash_struct, SHA256));
}
