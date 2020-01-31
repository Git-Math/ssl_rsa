/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_rsa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:23:07 by mnguyen           #+#    #+#             */
/*   Updated: 2020/01/30 17:23:10 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_rsa.h"

void	error_rsa(enum e_error e, char *s)
{
	if (e == INVALID_GENRSA_OPTS)
	{
		ft_putsterr("ft_ssl: genrsa: Error: '");
		ft_putsterr(s);
		ft_putsterr("' is an invalid option.\n\nOptions :\n-i : input file\n\
		-o : output file\n");
	}
	else if (e == OPEN_FAILED)
		ft_putsterr("ft_ssl: Error: open failed.\n");
	else if (e == GENRSA_KEY_GCD_ERROR)
		ft_putsterr("ft_ssl: genrsa: Error: invalid gcd in key generation.\n");
}
