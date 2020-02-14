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

void	error_rsa0(enum e_error e, char *s)
{
	if (e == OPT_PASS_NO_VALUE)
		ft_putsterr("ft_ssl: Error: option -[passin|passout] with no data.\n\n\
usage: ft_ssl command -[passin|passout] \"exemple\"\n");
	else if (e == OPT_PASS_TOO_BIG)
		ft_putsterr("ft_ssl: Error: option -[passin|passout] with string too \
big, size max: 1 048 576.\n");
	else if (e == INVALID_RSA_PEM)
	{
		ft_putsterr("ft_ssl: rsa: Error: invalid rsa pem: ");
		ft_putsterr(s);
	}
	else if (e == INVALID_RSA_ASN1)
	{
		ft_putsterr("ft_ssl: rsa: Error: invalid rsa asn1: ");
		ft_putsterr(s);
	}
	else if (e == PUBIN_CHECK)
		ft_putsterr("Only private keys can be checked\n");
}

void	error_rsa(enum e_error e, char *s)
{
	if (e == INVALID_GENRSA_OPTS)
	{
		ft_putsterr("ft_ssl: genrsa: Error: '");
		ft_putsterr(s);
		ft_putsterr("' is an invalid option.\n\nOptions :\n-i : input file\n\
-o : output file\n");
	}
	else if (e == INVALID_RSA_OPTS)
	{
		ft_putsterr("ft_ssl: rsa: Error: '");
		ft_putsterr(s);
		ft_putsterr("' is an invalid option.\n\nft_ssl rsa [-inform PEM] \
[-outform PEM] [-in file] [-passin arg] [-out file] [-passout arg] [-des] \
[-text] [-noout] [-modulus] [-check] [-pubin] [-pubout]\n");
	}
	else if (e == OPEN_FAILED)
		ft_putsterr("ft_ssl: Error: open failed.\n");
	else if (e == GENRSA_KEY_GCD_ERROR)
		ft_putsterr("ft_ssl: genrsa: Error: invalid gcd in key generation.\n");
	else if (e == INVALID_OPT_FORM)
		ft_putsterr("ft_ssl: Error: option -[inform|outform] with invalid value\
.\n\nusage: ft_ssl rsa -[inform|outform] \"PEM\"\n");
	else
		error_rsa0(e, s);
}
