/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opts_kpsv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 00:38:16 by mnguyen           #+#    #+#             */
/*   Updated: 2019/11/07 00:38:19 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_des.h"

void	set_kpsv(char **av, char opt, t_args *args, const int i)
{
	if (opt == 'k')
	{
		args->key.bytes = (t_byte *)av[i];
		args->key.size = ft_strlen(av[i]);
	}
	else if (opt == 'p')
	{
		args->password.bytes = (t_byte *)av[i];
		args->password.size = ft_strlen(av[i]);
	}
	else if (opt == 's')
	{
		args->salt.bytes = (t_byte *)av[i];
		args->salt.size = ft_strlen(av[i]);
	}
	else if (opt == 'v')
	{
		args->iv.bytes = (t_byte *)av[i];
		args->iv.size = ft_strlen(av[i]);
	}
}

void	get_opts_kpsv(int ac, char **av, t_args *args)
{
	int	i;

	if (!(args->opts & OPT_K) && !(args->opts & OPT_PD) \
		&& !(args->opts & OPT_SD) && !(args->opts & OPT_V))
		return ;
	i = 2;
	while (i < ac)
	{
		if (ft_strlen(av[i]) == 2 && av[i][0] == '-' && (av[i][1] == 'k' \
			|| av[i][1] == 'p' || av[i][1] == 's' || av[i][1] == 'v'))
		{
			i += 1;
			if (i == ac)
				error_free_args(OPT_KPSV_NO_VALUE, "", args);
			else if (ft_strlen(av[i]) >= DATA_SIZE_MAX)
				error_free_args(OPT_KPSV_TOO_BIG, "", args);
			set_kpsv(av, av[i - 1][1], args, i);
		}
		i += 1;
	}
}
