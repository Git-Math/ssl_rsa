/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_des.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 00:37:40 by mnguyen           #+#    #+#             */
/*   Updated: 2019/11/07 00:37:45 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

void	get_opts_des_exclusive(char **av, t_args *args, int *i)
{
	if (av[*i][1] == 'a')
		args->opts = args->opts | OPT_A;
	else if (av[*i][1] == 'k')
	{
		args->opts = args->opts | OPT_K;
		*i += 1;
	}
	else if (av[*i][1] == 'p')
	{
		args->opts = args->opts | OPT_PD;
		*i += 1;
	}
	else if (av[*i][1] == 's')
	{
		args->opts = args->opts | OPT_SD;
		*i += 1;
	}
	else if (av[*i][1] == 'v')
	{
		args->opts = args->opts | OPT_V;
		*i += 1;
	}
	else
		error(INVALID_DES_OPTS, av[*i]);
}

void	get_opts_des(char **av, t_args *args, int *i)
{
	if (av[*i][1] == 'd')
		args->opts = args->opts | OPT_D;
	else if (av[*i][1] == 'e')
		args->opts = args->opts & ~OPT_D;
	else if (av[*i][1] == 'i')
	{
		args->opts = args->opts | OPT_I;
		*i += 1;
	}
	else if (av[*i][1] == 'o')
	{
		args->opts = args->opts | OPT_O;
		*i += 1;
	}
	else if (args->command != BASE64)
		get_opts_des_exclusive(av, args, i);
	else
		error(INVALID_BASE64_OPTS, av[*i]);
}

void	get_opts_io0(int ac, char **av, t_args *args, int i)
{
	if (i == ac)
		error_free_args(OPT_IO_NO_FILE, "", args);
	else if (ft_strlen(av[i]) == 0)
		error_free_args(OPT_IO_NO_FILE, "", args);
	else if (ft_strlen(av[i]) >= FILENAME_SIZE_MAX)
		error_free_args(FILENAME_TOO_BIG, "", args);
	if (av[i - 1][1] == 'i' && args->command != GENRSA)
	{
		args->data[0].bytes = (t_byte *)av[i];
		args->data[0].size = ft_strlen(av[i]);
	}
	else if (av[i - 1][1] == 'o')
	{
		args->out_file.bytes = (t_byte *)av[i];
		args->out_file.size = ft_strlen(av[i]);
	}
}

void	get_opts_io(int ac, char **av, t_args *args)
{
	int i;

	if (!(args->opts & OPT_I) && !(args->opts & OPT_O))
		return ;
	i = 2;
	while (i < ac)
	{
		if (ft_strlen(av[i]) == 2 && av[i][0] == '-' && (av[i][1] == 'i' \
			|| av[i][1] == 'o'))
		{
			i += 1;
			get_opts_io0(ac, av, args, i);
		}
		i += 1;
	}
}
