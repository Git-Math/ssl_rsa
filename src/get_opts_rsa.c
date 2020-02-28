/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opts_rsa.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 13:41:06 by mnguyen           #+#    #+#             */
/*   Updated: 2020/02/13 13:41:20 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_rsa.h"

void	get_opts_form(int ac, char **av, t_args *args)
{
	int	i;

	if (!(args->opts & OPT_INF) && !(args->opts & OPT_OUTF))
		return ;
	i = 2;
	while (i < ac)
	{
		if ((ft_strlen(av[i]) == 7 && !ft_memcmp(av[i], "-inform", 7)) \
			|| (ft_strlen(av[i]) == 8 && !ft_memcmp(av[i], "-outform", 8)))
		{
			i += 1;
			if (i == ac \
				|| (ft_strlen(av[i]) != 3 || ft_memcmp(av[i], "PEM", 3)))
				error_free_args(INVALID_OPT_FORM, "", args);
		}
		i += 1;
	}
}

void	set_pass(char **av, char opt, t_args *args, const int i)
{
	if (opt == 'i')
	{
		args->passin.bytes = (t_byte *)av[i];
		args->passin.size = ft_strlen(av[i]);
	}
	else if (opt == 'o')
	{
		args->passout.bytes = (t_byte *)av[i];
		args->passout.size = ft_strlen(av[i]);
	}
}

void	get_opts_pass(int ac, char **av, t_args *args)
{
	int	i;

	if (!(args->opts & OPT_PASSIN) && !(args->opts & OPT_PASSOUT))
		return ;
	i = 2;
	while (i < ac)
	{
		if ((ft_strlen(av[i]) == 7 && !ft_memcmp(av[i], "-passin", 7)) \
			|| (ft_strlen(av[i]) == 8 && !ft_memcmp(av[i], "-passout", 8)))
		{
			i += 1;
			if (i == ac)
				error_free_args(OPT_PASS_NO_VALUE, "", args);
			else if (ft_strlen(av[i]) >= DATA_SIZE_MAX)
				error_free_args(OPT_PASS_TOO_BIG, "", args);
			set_pass(av, av[i - 1][5], args, i);
		}
		i += 1;
	}
}

void	get_opts_inkey(int ac, char **av, t_args *args)
{
	int	i;

	if (!(args->opts & OPT_INKEY))
		return ;
	i = 2;
	while (i < ac)
	{
		if (ft_strlen(av[i]) == 6 && !ft_memcmp(av[i], "-inkey", 6))
		{
			i += 1;
			if (i == ac)
				error_free_args(OPT_INKEY_NO_FILE, "", args);
			else if (ft_strlen(av[i]) == 0)
				error_free_args(OPT_INKEY_NO_FILE, "", args);
			else if (ft_strlen(av[i]) >= FILENAME_SIZE_MAX)
				error_free_args(FILENAME_TOO_BIG, "", args);
			args->inkey_file.bytes = (t_byte *)av[i];
			args->inkey_file.size = ft_strlen(av[i]);
		}
		i += 1;
	}
}
