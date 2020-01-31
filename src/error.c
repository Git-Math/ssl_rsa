/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 18:53:15 by mnguyen           #+#    #+#             */
/*   Updated: 2019/01/14 18:06:40 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_md5.h"
#include "ssl_des.h"
#include "ssl_rsa.h"

void	error0(enum e_error e, char *s)
{
	if (e == NO_COMMAND)
		ft_putsterr("usage: ft_ssl command [command opts] [command args]\n");
	else if (e == INVALID_COMMAND)
	{
		ft_putsterr("ft_ssl: Error: '");
		ft_putsterr(s);
		ft_putsterr("' is an invalid command.\n\nStandard commands :\n\
genrsa\nrsa\nrsault\n\n\
Message Digest commands :\nmd5\nsha224\nsha256\nsha384\nsha512\n\n\
Cipher commands:\nbase64\ndes\ndes-ecb\ndes-cbc\ndes_pcbc\ndes-cfb\n\
des-ofb\ndes3\ndes3-ecb\ndes3-cbc\ndes3_pcbc\ndes3-cfb\ndes3-ofb\n");
	}
	else if (e == INVALID_OPTS)
	{
		ft_putsterr("ft_ssl: Error: '");
		ft_putsterr(s);
		ft_putsterr("' is an invalid option.\n\nOptions :\n-p : echo STDIN \
to STDOUT and append the checksum to STDOUT\n-q : quiet mode\
\n-r : reverse the format of the output\n-s : \
print the sum of the given string\n");
	}
	else if (e == OPT_S_TOO_BIG)
		ft_putsterr("ft_ssl: Error: option -s with stdin too big, size max \
: 1 048 576.\n");
}

void	error(enum e_error e, char *s)
{
	error_des(e, s);
	error0(e, s);
	error_rsa(e, s);
	if (e == OPT_S_NO_DATA)
		ft_putsterr("ft_ssl: Error: option -s with no data.\n\n\
usage: ft_ssl command -s \"exemple\"\n");
	else if (e == OPT_S_TOO_BIG)
		ft_putsterr("ft_ssl: Error: option -s with string too big, size max \
: 1 048 576.\n");
	else if (e == FILENAME_TOO_BIG)
		ft_putsterr("ft_ssl: Error: filename size too big, size max : 128.\n");
	else if (e == MALLOC_FAILED)
		ft_putsterr("ft_ssl: Error: malloc failed.\n");
	exit(0);
}

void	free_args(t_args *args)
{
	if (args->opts & OPT_P || args->opts & OPT_NO)
		free(args->data[0].bytes);
	free(args->data);
}

void	error_free_args(enum e_error e, char *s, t_args *args)
{
	free_args(args);
	error(e, s);
}

int		ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
