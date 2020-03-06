/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 19:21:38 by mnguyen           #+#    #+#             */
/*   Updated: 2018/12/12 19:23:40 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_md5.h"
#include "ssl_des.h"
#include "ssl_rsa.h"

void	get_command(int ac, char **av, t_args *args)
{
	if (ac < 2)
		error(NO_COMMAND, "");
	else if (ft_strlen(av[1]) == 3 && !ft_memcmp(av[1], "md5", 3))
		args->command = MD5;
	else if (ft_strlen(av[1]) == 6 && !ft_memcmp(av[1], "sha224", 6))
		args->command = SHA224;
	else if (ft_strlen(av[1]) == 6 && !ft_memcmp(av[1], "sha256", 6))
		args->command = SHA256;
	else if (ft_strlen(av[1]) == 6 && !ft_memcmp(av[1], "sha384", 6))
		args->command = SHA384;
	else if (ft_strlen(av[1]) == 6 && !ft_memcmp(av[1], "sha512", 6))
		args->command = SHA512;
	else if (ft_strlen(av[1]) == 6 && !ft_memcmp(av[1], "base64", 6))
		args->command = BASE64;
	else
		get_command_des(av, args);
}

void	get_opts(int ac, char **av, t_args *args, int *i)
{
	args->opts = 0;
	args->opt_s_nb = 0;
	args->i = 0;
	while (*i < ac && av[*i][0] == '-')
	{
		if (ft_strlen(av[*i]) != 2 && args->command != RSA \
			&& args->command != RSAUTL && args->command != BREAK_RSA)
			error(INVALID_OPTS, av[*i]);
		if (args->command >= GENRSA && args->command <= BREAK_RSA)
			get_opts_rsa(av, args, i);
		else if (args->command <= SHA512)
			get_opts_mdc(av, args, i);
		else if (args->command >= BASE64)
			get_opts_des(av, args, i);
		*i += 1;
	}
	args->command == GENDES && *i < ac ? error(INVALID_GENDES_OPTS, av[*i]) : 0;
	args->command == GENDSA && *i < ac ? error(INVALID_GENDSA_OPTS, av[*i]) : 0;
	args->command == RSAUTL && *i < ac ? error(INVALID_RSAUTL_OPTS, av[*i]) : 0;
	args->command == RSA && *i < ac ? error(INVALID_RSA_OPTS, av[*i]) : 0;
	args->command == GENRSA && *i < ac ? error(INVALID_GENRSA_OPTS, av[*i]) : 0;
	args->command == BASE64 && *i < ac ? error(INVALID_BASE64_OPTS, av[*i]) : 0;
	args->command >= DES_ECB && *i < ac ? error(INVALID_DES_OPTS, av[*i]) : 0;
	if (*i == ac && !(args->opts & OPT_S) && !(args->opts & OPT_I))
		args->opts = args->opts | OPT_NO;
}

void	get_opts_s(int ac, char **av, t_args *args)
{
	int i;

	if (!(args->opts & OPT_S))
		return ;
	i = 2;
	while (i < ac && av[i][0] == '-')
	{
		if (ft_strlen(av[i]) == 2 && av[i][1] == 's')
		{
			i += 1;
			if (i == ac)
				error_free_args(OPT_S_NO_DATA, "", args);
			else if (ft_strlen(av[i]) == 0)
				error_free_args(OPT_S_NO_DATA, "", args);
			else if (ft_strlen(av[i]) > DATA_SIZE_MAX)
				error_free_args(OPT_S_TOO_BIG, "", args);
			args->data[args->i].bytes = (t_byte *)av[i];
			args->data[args->i].size = ft_strlen(av[i]);
			args->i++;
		}
		i += 1;
	}
}

void	get_filenames(int ac, char **av, t_args *args, int *i)
{
	while (*i < ac)
	{
		if (ft_strlen(av[*i]) >= FILENAME_SIZE_MAX)
			error_free_args(FILENAME_TOO_BIG, "", args);
		args->data[args->i].bytes = (t_byte *)av[*i];
		args->data[args->i].size = ft_strlen(av[*i]);
		args->i++;
		*i += 1;
	}
}

t_args	get_args(int ac, char **av)
{
	t_args		args;
	int			i;

	i = 2;
	get_command(ac, av, &args);
	get_opts(ac, av, &args, &i);
	set_dispatcher(&args);
	set_mem_data(ac, &args, &i);
	get_opts_s(ac, av, &args);
	get_opts_io(ac, av, &args);
	get_opts_kpsv(ac, av, &args);
	get_opts_form(ac, av, &args);
	get_opts_pass(ac, av, &args);
	get_opts_inkey(ac, av, &args);
	get_filenames(ac, av, &args, &i);
	return (args);
}
