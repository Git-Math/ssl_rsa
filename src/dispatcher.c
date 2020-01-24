/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 13:58:35 by mnguyen           #+#    #+#             */
/*   Updated: 2019/01/14 13:59:14 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_md5.h"
#include "ssl_des.h"

void	set_md5_dispatcher(t_args *args)
{
	args->disp.cmd = "MD5";
	args->disp.set = &set_md5_struct;
	args->disp.free = &free_md5_struct;
	args->disp.hash = &md5;
}

void	set_sha224_256_dispatcher(t_args *args)
{
	if (args->command == SHA224)
	{
		args->disp.cmd = "SHA224";
		args->disp.set = &set_sha224_struct;
		args->disp.hash = &sha224;
	}
	else
	{
		args->disp.cmd = "SHA256";
		args->disp.set = &set_sha256_struct;
		args->disp.hash = &sha256;
	}
	args->disp.free = &free_sha256_struct;
}

void	set_sha384_512_dispatcher(t_args *args)
{
	if (args->command == SHA384)
	{
		args->disp.cmd = "SHA384";
		args->disp.set = &set_sha384_struct;
		args->disp.hash = &sha384;
	}
	else
	{
		args->disp.cmd = "SHA512";
		args->disp.set = &set_sha512_struct;
		args->disp.hash = &sha512;
	}
	args->disp.free = &free_sha512_struct;
}

void	set_dispatcher(t_args *args)
{
	if (args->command == MD5)
		set_md5_dispatcher(args);
	else if (args->command == SHA224 || args->command == SHA256)
		set_sha224_256_dispatcher(args);
	else if (args->command == SHA384 || args->command == SHA512)
		set_sha384_512_dispatcher(args);
	else if (args->command == BASE64)
		set_base64_dispatcher(args);
	else if (args->command >= DES_ECB)
		set_des_dispatcher(args);
}
