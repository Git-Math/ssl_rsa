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

void	get_opts_rsa(char **av, t_args *args, int *i)
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
	else
		error(INVALID_GENRSA_OPTS, av[*i]);
}
