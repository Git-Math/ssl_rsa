/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_opts_mdc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 01:32:10 by mnguyen           #+#    #+#             */
/*   Updated: 2019/11/07 01:32:12 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_md5.h"
#include "ssl_des.h"

void	get_opts_mdc(char **av, t_args *args, int *i)
{
	if (av[*i][1] == 'p')
		args->opts = args->opts | OPT_P;
	else if (av[*i][1] == 'q')
		args->opts = args->opts | OPT_Q;
	else if (av[*i][1] == 'r')
		args->opts = args->opts | OPT_R;
	else if (av[*i][1] == 's')
	{
		args->opts = args->opts | OPT_S;
		*i += 1;
		args->opt_s_nb += 1;
	}
	else
		error(INVALID_OPTS, av[*i]);
}
