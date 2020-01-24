/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher_des.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 00:37:59 by mnguyen           #+#    #+#             */
/*   Updated: 2019/11/07 00:38:00 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

void	set_base64_dispatcher(t_args *args)
{
	args->disp.cmd = "BASE64";
	args->disp.set = &set_base64_struct;
	args->disp.free = &free_base64_struct;
	if (args->opts & OPT_D)
		args->disp.hash = &base64_decode;
	else
		args->disp.hash = &base64_encode;
}

void	set_des_dispatcher(t_args *args)
{
	if (args->command == DES_ECB)
		args->disp.cmd = "DES_ECB";
	else if (args->command == DES_CBC)
		args->disp.cmd = "DES_CBC";
	else if (args->command == DES_PCBC)
		args->disp.cmd = "DES_PCBC";
	else if (args->command == DES_CFB)
		args->disp.cmd = "DES_CFB";
	else if (args->command == DES_OFB)
		args->disp.cmd = "DES_OFB";
	else if (args->command == DES3_ECB)
		args->disp.cmd = "DES3_ECB";
	else if (args->command == DES3_CBC)
		args->disp.cmd = "DES3_CBC";
	else if (args->command == DES3_PCBC)
		args->disp.cmd = "DES3_PCBC";
	else if (args->command == DES3_CFB)
		args->disp.cmd = "DES3_CFB";
	else if (args->command == DES3_OFB)
		args->disp.cmd = "DES3_OFB";
	args->disp.set = &set_des_struct;
	args->disp.free = &free_des_struct;
	args->disp.hash = (args->command >= DES3_ECB ? &des3 : &des);
}
