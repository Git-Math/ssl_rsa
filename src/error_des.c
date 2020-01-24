/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_des.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 00:38:52 by mnguyen           #+#    #+#             */
/*   Updated: 2019/11/07 00:38:54 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

void	error_base64(enum e_error e, char *s)
{
	if (e == INVALID_BASE64_OPTS)
	{
		ft_putsterr("ft_ssl: base64: Error: '");
		ft_putsterr(s);
		ft_putsterr("' is an invalid option.\n\nOptions :\n-d : decode mode\n\
-e : encode mode (default)\n-i : input file\n-o : output file\n");
	}
	else if (e == INVALID_INPUT)
	{
		ft_putsterr("ft_ssl: ");
		ft_putsterr(s);
		ft_putsterr(": Error: invalid input\n");
	}
}

void	error_des0(enum e_error e)
{
	if (e == OPT_KPSV_NO_VALUE)
		ft_putsterr("ft_ssl: Error: option -[kpsv] with no data.\n\n\
usage: ft_ssl command -[kpsv] \"exemple\"\n");
	else if (e == OPT_KPSV_TOO_BIG)
		ft_putsterr("ft_ssl: Error: option -[kpsv] with string too big, \
size max: 1 048 576.\n");
	else if (e == INVALID_HEX)
		ft_putsterr("ft_ssl: Error: invalid hex value: \
non hexadecimal digit\n");
	else if (e == INVALID_PASSWORD)
		ft_putsterr("ft_ssl: Error: invalid password\n");
}

void	error_des(enum e_error e, char *s)
{
	error_base64(e, s);
	if (e == INVALID_DES_OPTS)
	{
		ft_putsterr("ft_ssl: des: Error: '");
		ft_putsterr(s);
		ft_putsterr("' is an invalid option.\n\nOptions :\n\
-a : decode/encode the input/output in base64\n-d : decrypt mode\n\
-e : encrypt mode (default)\n-i : input file for message\n\
-k : key in hex is the next argument\n-o : output file for message\n\
-p : password in ascii is the next argument\n\
-s : the salt in hex is the next argument\n\
-v : initialization vector in hex is the next argument\n");
	}
	else if (e == OPT_IO_NO_FILE)
		ft_putsterr("ft_ssl: Error: option -i or -o with no file name.\n\n\
usage: ft_ssl command -i input_file.txt -o output_file.txt\n");
	else
		error_des0(e);
}
