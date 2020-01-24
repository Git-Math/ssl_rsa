/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 19:20:03 by mnguyen           #+#    #+#             */
/*   Updated: 2018/12/12 19:21:12 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_md5.h"
#include "ssl_des.h"

t_bool	exec_error_read_files(t_args *args, t_buffer *data)
{
	if (data->size == (DATA_SIZE_MAX + 1) || data->size < 0 || data->size == 0)
	{
		ft_putsterr("ft_ssl: ");
		print_bufferr(args->data[args->i]);
		if (data->size > DATA_SIZE_MAX)
			ft_putsterr(": Data size too big\n");
		else if (data->size < 0)
			ft_putsterr(": No such file or directory\n");
		else if (data->size == 0)
			ft_putsterr(": No data\n");
		close(args->fd);
		args->i++;
		return (FALSE);
	}
	return (TRUE);
}

t_bool	exec_read_files(t_args *args, t_buffer *data)
{
	args->fd = open((const char *)args->data[args->i].bytes, O_RDONLY);
	if (args->fd < 0)
	{
		ft_putsterr("ft_ssl: ");
		print_bufferr(args->data[args->i]);
		ft_putsterr(": No such file or directory\n");
		args->i++;
		return (FALSE);
	}
	data->size = read(args->fd, data->bytes, DATA_SIZE_MAX + 1);
	return (exec_error_read_files(args, data));
}

void	exec_print_result(t_args *args, t_buffer result)
{
	if (args->opts & OPT_Q)
	{
		print_buffer_hex(result);
		ft_putchar('\n');
	}
	else if (args->opts & OPT_R)
	{
		print_buffer_hex(result);
		ft_putstr(" ");
		print_buffer(args->data[args->i]);
		ft_putstr("\n");
	}
	else
	{
		ft_putstr(args->disp.cmd);
		ft_putstr(" (");
		print_buffer(args->data[args->i]);
		ft_putstr(") = ");
		print_buffer_hex(result);
		ft_putchar('\n');
	}
}

void	exec_command_files(t_args *args, t_buffer data)
{
	t_buffer	result;
	void		*hash_struct;

	hash_struct = args->disp.set(data);
	if (args->command >= DES_ECB)
		set_des_exclusive(args, hash_struct);
	result = args->disp.hash(hash_struct);
	args->disp.free(hash_struct);
	if (result.size == 0)
		error_free_args(INVALID_INPUT, args->disp.cmd, args);
	if (args->command >= DES_ECB)
		print_des_result(args, result);
	else if (args->command == BASE64)
		print_base64_buffer(args, result);
	else
		exec_print_result(args, result);
	free(result.bytes);
}

void	exec_files(t_args *args)
{
	t_buffer data;

	data.bytes = malloc(sizeof(unsigned char) * (DATA_SIZE_MAX + 1));
	if (data.bytes == NULL)
		error(MALLOC_FAILED, "");
	while (args->i < args->data_size)
	{
		if (!exec_read_files(args, &data))
			continue;
		exec_command_files(args, data);
		close(args->fd);
		args->i++;
	}
	free(data.bytes);
}
