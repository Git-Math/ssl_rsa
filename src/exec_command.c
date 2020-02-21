/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 19:16:28 by mnguyen           #+#    #+#             */
/*   Updated: 2018/12/12 19:19:26 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_md5.h"
#include "ssl_des.h"
#include "ssl_rsa.h"

void	exec_opt_p(t_args *args)
{
	t_buffer	result;
	void		*hash_struct;

	args->i = 0;
	if (args->opts & OPT_P || args->opts & OPT_NO)
	{
		hash_struct = args->disp.set(args->data[args->i]);
		(args->command >= DES_ECB) ? set_des_exclusive(args, hash_struct) : 0;
		result = args->disp.hash(hash_struct);
		args->disp.free(hash_struct);
		if (result.size == 0)
			error_free_args(INVALID_INPUT, args->disp.cmd, args);
		if (args->command >= DES_ECB)
			print_des_result(args, result);
		else if (args->command >= BASE64)
			print_base64_buffer(args, result);
		else
		{
			(args->opts & OPT_P) ? print_buffer(args->data[args->i]) : 0;
			print_buffer_hex(result);
			ft_putchar('\n');
		}
		free(result.bytes);
		args->i++;
	}
}

void	exec_print_opt_s(t_args *args, t_buffer result)
{
	if (args->opts & OPT_Q)
	{
		print_buffer_hex(result);
		ft_putchar('\n');
	}
	else if (args->opts & OPT_R)
	{
		print_buffer_hex(result);
		ft_putstr(" \"");
		print_buffer(args->data[args->i]);
		ft_putstr("\"\n");
	}
	else
	{
		ft_putstr(args->disp.cmd);
		ft_putstr(" (\"");
		print_buffer(args->data[args->i]);
		ft_putstr("\") = ");
		print_buffer_hex(result);
		ft_putchar('\n');
	}
}

void	exec_opt_s(t_args *args)
{
	t_buffer	result;
	int			i;
	void		*hash_struct;

	i = 0;
	while (i < args->opt_s_nb)
	{
		hash_struct = args->disp.set(args->data[args->i]);
		result = args->disp.hash(hash_struct);
		args->disp.free(hash_struct);
		exec_print_opt_s(args, result);
		free(result.bytes);
		args->i++;
		i++;
	}
}

void	exec_command(t_args args)
{
	if (args.command == GENRSA)
		print_rsa_key(&args, genrsa(), TRUE, FALSE);
	else if (args.command == RSA)
		rsa(&args);
	else
	{
		exec_opt_p(&args);
		exec_opt_s(&args);
		exec_files(&args);
		free_args(&args);
	}
}
