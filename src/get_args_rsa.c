/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_rsa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:33:50 by mnguyen           #+#    #+#             */
/*   Updated: 2020/01/30 17:33:52 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_rsa.h"

void	get_opts_gen(char **av, t_args *args, int *i)
{
	if (av[*i][1] == 'i')
	{
		args->opts = args->opts | OPT_I;
		*i += 1;
	}
	else if (av[*i][1] == 'o')
	{
		args->opts = args->opts | OPT_O;
		*i += 1;
	}
	else if (args->command == GENRSA)
		error(INVALID_GENRSA_OPTS, av[*i]);
	else if (args->command == GENDSA)
		error(INVALID_GENDSA_OPTS, av[*i]);
	else
		error(INVALID_GENDES_OPTS, av[*i]);
}

void	get_opts_rsa_c0(char **av, t_args *args, int *i)
{
	if (ft_strlen(av[*i]) == 4 && !ft_memcmp(av[*i], "-out", 4))
	{
		args->opts = args->opts | OPT_O;
		*i += 1;
	}
	else if (ft_strlen(av[*i]) == 8 && !ft_memcmp(av[*i], "-passout", 8))
	{
		args->opts = args->opts | OPT_PASSOUT;
		*i += 1;
	}
	else if (ft_strlen(av[*i]) == 5 && !ft_memcmp(av[*i], "-text", 5))
		args->opts = args->opts | OPT_TEXT;
	else if (ft_strlen(av[*i]) == 6 && !ft_memcmp(av[*i], "-noout", 6))
		args->opts = args->opts | OPT_NOOUT;
	else if (ft_strlen(av[*i]) == 8 && !ft_memcmp(av[*i], "-modulus", 8))
		args->opts = args->opts | OPT_MODULUS;
	else if (ft_strlen(av[*i]) == 6 && !ft_memcmp(av[*i], "-check", 6))
		args->opts = args->opts | OPT_CHECK;
	else if (ft_strlen(av[*i]) == 6 && !ft_memcmp(av[*i], "-pubin", 6))
		args->opts = args->opts | OPT_PUBIN;
	else if (ft_strlen(av[*i]) == 7 && !ft_memcmp(av[*i], "-pubout", 7))
		args->opts = args->opts | OPT_PUBOUT;
	else
		error(INVALID_RSA_OPTS, av[*i]);
}

void	get_opts_rsa_c(char **av, t_args *args, int *i)
{
	if (ft_strlen(av[*i]) == 7 && !ft_memcmp(av[*i], "-inform", 7))
	{
		args->opts = args->opts | OPT_INF;
		*i += 1;
	}
	else if (ft_strlen(av[*i]) == 8 && !ft_memcmp(av[*i], "-outform", 8))
	{
		args->opts = args->opts | OPT_OUTF;
		*i += 1;
	}
	else if (ft_strlen(av[*i]) == 3 && !ft_memcmp(av[*i], "-in", 3))
	{
		args->opts = args->opts | OPT_I;
		*i += 1;
	}
	else if (ft_strlen(av[*i]) == 7 && !ft_memcmp(av[*i], "-passin", 7))
	{
		args->opts = args->opts | OPT_PASSIN;
		*i += 1;
	}
	else if (ft_strlen(av[*i]) == 4 && !ft_memcmp(av[*i], "-des", 4))
		args->opts = args->opts | OPT_DES;
	else
		get_opts_rsa_c0(av, args, i);
}

void	get_opts_rsautl(char **av, t_args *args, int *i)
{
	if (ft_strlen(av[*i]) == 3 && !ft_memcmp(av[*i], "-in", 3))
	{
		args->opts = args->opts | OPT_I;
		*i += 1;
	}
	else if (ft_strlen(av[*i]) == 4 && !ft_memcmp(av[*i], "-out", 4))
	{
		args->opts = args->opts | OPT_O;
		*i += 1;
	}
	else if (ft_strlen(av[*i]) == 6 && !ft_memcmp(av[*i], "-inkey", 6))
	{
		args->opts = args->opts | OPT_INKEY;
		*i += 1;
	}
	else if (ft_strlen(av[*i]) == 6 && !ft_memcmp(av[*i], "-pubin", 6))
		args->opts = args->opts | OPT_PUBIN;
	else if (ft_strlen(av[*i]) == 8 && !ft_memcmp(av[*i], "-encrypt", 8))
		args->opts = args->opts & ~OPT_D;
	else if (ft_strlen(av[*i]) == 8 && !ft_memcmp(av[*i], "-decrypt", 8))
		args->opts = args->opts | OPT_D;
	else if (ft_strlen(av[*i]) == 8 && !ft_memcmp(av[*i], "-hexdump", 8))
		args->opts = args->opts | OPT_HEXDUMP;
	else
		error(INVALID_RSAUTL_OPTS, av[*i]);
}

void	get_opts_rsa(char **av, t_args *args, int *i)
{
	if (args->command == GENRSA || args->command == GENDSA \
								|| args->command == GENDES)
		get_opts_gen(av, args, i);
	else if (args->command == RSA)
	{
		get_opts_rsa_c(av, args, i);
		if ((args->opts & OPT_PUBIN) && (args->opts & OPT_CHECK))
			error(PUBIN_CHECK, "");
	}
	else if (args->command == RSAUTL || args->command == BREAK_RSA)
	{
		get_opts_rsautl(av, args, i);
		if ((args->opts & OPT_PUBIN) && (args->opts & OPT_D))
			error(PUBIN_DECRYPT, "");
	}
}
