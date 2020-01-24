/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha384_512.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:20:55 by mnguyen           #+#    #+#             */
/*   Updated: 2019/01/14 15:21:24 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_md5.h"

void		*set_sha384_struct(t_buffer data)
{
	return (set_sha384_512_struct(data, SHA384));
}

void		*set_sha512_struct(t_buffer data)
{
	return (set_sha384_512_struct(data, SHA512));
}

t_buffer	sha384(void *hash_struct)
{
	return (sha384_512(hash_struct, SHA384));
}

t_buffer	sha512(void *hash_struct)
{
	return (sha384_512(hash_struct, SHA512));
}
