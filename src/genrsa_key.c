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
#include <stdio.h>
t_uint64	mod_inverse(t_uint64 a, t_uint64 m)
{
	t_int64		x;
	t_int64		y;

	if (gcd_extended(a, m, &x, &y) != 1)
		error(GENRSA_KEY_GCD_ERROR, "");
	return (((x % (t_int64)m) + (t_int64)m) % mm);
}

void		genrsa_key(t_uint64 p, t_uint64 q, t_uint64 e)
{
	t_uint64	n;
	t_uint64	lambda;
	t_uint64	d;

	n = p * q;
	lambda = lcm(p - 1, q - 1);
	d = mod_inverse(e, lambda);
	printf("p = %lu, q = %lu, n = %lu, lambda = %lu, d = %lu\n", p, q, n, lambda, d);
}
