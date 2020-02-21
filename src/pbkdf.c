/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pbkdf.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 00:37:23 by mnguyen           #+#    #+#             */
/*   Updated: 2019/11/07 00:37:24 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"
#include "ssl_rsa.h"

void	get_pass_salt(t_args *args, t_buffer *salt)
{
	if (!(args->opts & OPT_PD))
	{
		args->password.bytes = (t_byte *)getpass("enter encryption password: ");
		args->password.size = ft_strlen((char *)args->password.bytes);
		if (args->password.size == 0)
			error_free_args(INVALID_PASSWORD, "", args);
	}
	if (!(args->opts & OPT_SD))
	{
		salt->size = 8;
		salt->bytes = rand_bytes(salt->size);
	}
	else
		*salt = buffer_hex_to_byte(args, args->salt, 8);
}

void	set_key_iv(t_args *args, t_des *des_struct, t_buffer dk)
{
	if (!(args->opts & OPT_K))
	{
		des_struct->key.size = args->command >= DES3_ECB ? 24 : 8;
		des_struct->key.bytes = malloc(sizeof(t_byte) * des_struct->key.size);
		ft_memcpy(des_struct->key.bytes, dk.bytes, des_struct->key.size);
	}
	if (!(args->opts & OPT_V))
	{
		des_struct->iv.size = 8;
		des_struct->iv.bytes = malloc(sizeof(t_byte) * des_struct->iv.size);
		ft_memcpy(des_struct->iv.bytes, dk.bytes + des_struct->key.size, \
			des_struct->iv.size);
	}
}

void	pbkdf_init(t_args *args, t_buffer *dk, \
	t_buffer *md5_data, t_buffer *salt)
{
	dk->size = 32;
	dk->bytes = malloc(sizeof(t_byte) * dk->size);
	md5_data->size = args->password.size + salt->size;
	md5_data->bytes = malloc(sizeof(t_byte) * md5_data->size);
	ft_memcpy(md5_data->bytes, args->password.bytes, args->password.size);
	ft_memcpy(md5_data->bytes + args->password.size, salt->bytes, salt->size);
}

void	pbkdf_init_md5_data(t_args *args, t_buffer *md5_data, \
	t_buffer md5_res, t_buffer salt)
{
	md5_data->size = md5_res.size + args->password.size + salt.size;
	md5_data->bytes = malloc(sizeof(t_byte) * md5_data->size);
	ft_memcpy(md5_data->bytes, md5_res.bytes, md5_res.size);
	ft_memcpy(md5_data->bytes + md5_res.size, args->password.bytes, \
		args->password.size);
	ft_memcpy(md5_data->bytes + md5_res.size + args->password.size, \
		salt.bytes, salt.size);
}

void	pbkdf(t_args *args, t_des *des_struct)
{
	t_buffer	dk;
	t_buffer	salt;
	t_buffer	md5_data;
	t_buffer	md5_res;
	void		*md5_struct;

	get_pass_salt(args, &salt);
	pbkdf_init(args, &dk, &md5_data, &salt);
	md5_struct = set_md5_struct(md5_data);
	md5_res = md5(md5_struct);
	ft_memcpy(dk.bytes, md5_res.bytes, 16);
	free_md5_struct(md5_struct);
	free(md5_data.bytes);
	pbkdf_init_md5_data(args, &md5_data, md5_res, salt);
	free(md5_res.bytes);
	md5_struct = set_md5_struct(md5_data);
	md5_res = md5(md5_struct);
	ft_memcpy(dk.bytes + 16, md5_res.bytes, 16);
	free_md5_struct(md5_struct);
	free(md5_data.bytes);
	free(md5_res.bytes);
	free(salt.bytes);
	set_key_iv(args, des_struct, dk);
	free(dk.bytes);
}
