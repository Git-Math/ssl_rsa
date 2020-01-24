/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 19:24:03 by mnguyen           #+#    #+#             */
/*   Updated: 2018/12/12 19:24:13 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_md5.h"
#include "ssl_rsa.h"
#include <stdio.h>

int		main(int ac, char **av)
{
	t_args		args;
	t_uint64	n;
	t_bool		p;

	//rand_bytes = (t_byte *)malloc(sizeof(t_byte) * 8); //TEMP protect
	//fd = open("/dev/urandom", O_RDONLY); //TEMP protect
	p = FALSE;
	while (!p)
	{
		n = rand_uint64(2, 4294967295);
		p = is_prime(n, 0.9999999999999999);
		if (p)
		{
			printf("n = %ld", n);
			printf(", is_prime = %s\n", p ? "TRUE" : "FALSE");
		}
	}
	args = get_args(ac, av);
	exec_command(args);

	return (0);
}
