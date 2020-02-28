/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rsa_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:15:14 by mnguyen           #+#    #+#             */
/*   Updated: 2020/02/06 17:15:16 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_rsa.h"
#include "ssl_des.h"

void		print_buffer_hex_fd(t_buffer buff, int fd)
{
	int				i;
	unsigned char	first;
	unsigned char	sec;

	i = 0;
	while (i < buff.size)
	{
		first = buff.bytes[i] >> 4;
		if (first < 10)
			ft_putuint64_fd(first, fd);
		else
			ft_putchar_fd(first - 10 + 'A', fd);
		sec = buff.bytes[i] & 0xf;
		if (sec < 10)
			ft_putuint64_fd(sec, fd);
		else
			ft_putchar_fd(sec - 10 + 'A', fd);
		i++;
	}
}

t_buffer	calc_key64(t_args *args, t_buffer key, t_bool is_private)
{
	t_des		*des_struct;
	t_buffer	key64;

	if (is_private && (args->opts & OPT_DES))
	{
		des_struct = (t_des *)set_des_struct(key);
		des_struct->encode = TRUE;
		des_struct->a = TRUE;
		des_struct->a3 = FALSE;
		des_struct->padding = TRUE;
		des_struct->mode = CBC;
		if (args->opts & OPT_PASSOUT)
		{
			args->password = args->passout;
			args->opts = args->opts | OPT_PD;
		}
		pbkdf(args, des_struct);
		key64 = des((void *)des_struct);
		args->opts = args->opts & (~OPT_PD);
		free_des_struct((void *)des_struct);
	}
	else
		key64 = base64_encode((void *)&key);
	free(key.bytes);
	return (key64);
}

void		print_key64(t_args *args, t_buffer key64, t_bool is_private)
{
	if (is_private && (args->opts & OPT_DES))
	{
		ft_putstr_fd("Proc-Type: 4,ENCRYPTED\nDEK-Info: DES-CBC,", args->fd);
		print_buffer_hex_fd(args->salt, args->fd);
		free(args->salt.bytes);
		ft_putstr_fd("\n\n", args->fd);
	}
	print_base64_encode_buffer0(args, key64);
}

void		print_rsa_key(t_args *args, t_buffer key, t_bool is_private, \
	t_bool is_fd_open)
{
	t_buffer	key64;

	key64 = calc_key64(args, key, is_private);
	if (!is_fd_open && (args->opts & OPT_O))
	{
		args->fd = open((const char *)args->out_file.bytes, \
			O_WRONLY | O_TRUNC | O_CREAT, 0777);
		if (args->fd < 0)
		{
			ft_putsterr("ft_ssl: ");
			print_bufferr(args->out_file);
			ft_putsterr(": couldn't open the file\n");
			return ;
		}
	}
	else if (!is_fd_open)
		args->fd = 1;
	is_private ? write(args->fd, "-----BEGIN RSA PRIVATE KEY-----\n", 32) \
				: write(args->fd, "-----BEGIN PUBLIC KEY-----\n", 27);
	print_key64(args, key64, is_private);
	is_private ? write(args->fd, "-----END RSA PRIVATE KEY-----\n", 30) \
				: write(args->fd, "-----END PUBLIC KEY-----\n", 25);
	close(args->fd);
	free(key64.bytes);
}
