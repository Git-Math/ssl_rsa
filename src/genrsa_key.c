/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genrsa_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 16:31:18 by mnguyen           #+#    #+#             */
/*   Updated: 2020/01/31 16:31:21 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_rsa.h"

t_uint64	gcd(t_uint64 a, t_uint64 b)
{
	if (b == 0)
		return (a);
	return (gcd(b, a % b));
}

t_uint64	lcm(t_uint64 a, t_uint64 b)
{
	return ((a * b) / gcd(a, b));
}

t_uint64	gcd_extended(t_uint64 a, t_uint64 b, t_int64 *x, t_int64 *y)
{
	t_uint64	gcd;
	t_int64		x1;
	t_int64		y1;

	if (b == 0)
	{
		*x = 1;
		*y = 0;
		return (a);
	}
	gcd = gcd_extended(b, a % b, &x1, &y1);
	*x = y1;
	*y = x1 - (a / b) * y1;
	return (gcd);
}

t_uint64	mod_inverse(t_uint64 a, t_uint64 m)
{
	t_int64		x;
	t_int64		y;

	if (gcd_extended(a, m, &x, &y) != 1)
		error(GENRSA_KEY_GCD_ERROR, "");
	return (((x % (t_int64)m) + (t_int64)m) % m);
}

t_buffer	genrsa_key(t_genrsa genrsa_struct)
{
	genrsa_struct.n = genrsa_struct.p * genrsa_struct.q;
	genrsa_struct.l = lcm(genrsa_struct.p - 1, genrsa_struct.q - 1);
	genrsa_struct.d = mod_inverse(genrsa_struct.e, genrsa_struct.l);
	return (genrsa_key_buffer(genrsa_struct));
}
