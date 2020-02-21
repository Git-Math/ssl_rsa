/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rsa_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 18:18:03 by mnguyen           #+#    #+#             */
/*   Updated: 2020/02/20 18:18:03 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_rsa.h"

void	check_rsa_key_exp_coef(t_rsa *rsa_struct, t_bool *check_ok)
{
	if (rsa_struct->exp1 != rsa_struct->d % (rsa_struct->p - 1))
	{
		ft_putsterr("exponent1 is not equal to private_exponent % (prime1 - 1)\
.\n");
		*check_ok = FALSE;
	}
	if (rsa_struct->exp2 != rsa_struct->d % (rsa_struct->q - 1))
	{
		ft_putsterr("exponent2 is not equal to private_exponent % (prime2 - 1)\
.\n");
		*check_ok = FALSE;
	}
	if (rsa_struct->coef != mod_inverse(rsa_struct->q, rsa_struct->p, FALSE))
	{
		ft_putsterr("coefficient is not the modular \
multiplicative inverse of prime2 modulo prime1.\n");
		*check_ok = FALSE;
	}
}

void	check_rsa_key_d_p_q(t_rsa *rsa_struct, t_uint64 l, t_bool *check_ok)
{
	if (rsa_struct->d != mod_inverse(rsa_struct->e, l, FALSE))
	{
		ft_putsterr("private_exponent is not the modular \
multiplicative inverse of public_exponent modulo l.\n");
		*check_ok = FALSE;
	}
	if (!is_prime(rsa_struct->p, 0.9999999999999999, FALSE))
	{
		ft_putsterr("prime1 is not prime.\n");
		*check_ok = FALSE;
	}
	if (!is_prime(rsa_struct->q, 0.9999999999999999, FALSE))
	{
		ft_putsterr("prime2 is not prime.\n");
		*check_ok = FALSE;
	}
	if (rsa_struct->p == rsa_struct->q)
	{
		ft_putsterr("prime1 equals prime2.\n");
		*check_ok = FALSE;
	}
}

void	check_rsa_key_n_e(t_rsa *rsa_struct, t_uint64 l, t_bool *check_ok)
{
	if (rsa_struct->n != rsa_struct->p * rsa_struct->q)
	{
		ft_putsterr("modulus is not equal to prime1 * prime2.\n");
		*check_ok = FALSE;
	}
	if (rsa_struct->e <= 1)
	{
		ft_putsterr("public_exponent is less or equal to 1.\n");
		*check_ok = FALSE;
	}
	if (rsa_struct->e >= l)
	{
		ft_putsterr("public_exponent is greater or equal to l.\n");
		*check_ok = FALSE;
	}
	if (gcd(rsa_struct->e, l) != 1)
	{
		ft_putsterr("public_exponent is not coprime with l.\n");
		*check_ok = FALSE;
	}
}

void	check_rsa_key(t_args *args, t_rsa *rsa_struct)
{
	t_bool		check_ok;
	t_uint64	l;

	check_ok = TRUE;
	l = lcm(rsa_struct->p - 1, rsa_struct->q - 1);
	check_rsa_key_n_e(rsa_struct, l, &check_ok);
	check_rsa_key_d_p_q(rsa_struct, l, &check_ok);
	check_rsa_key_exp_coef(rsa_struct, &check_ok);
	check_ok ? ft_putstr_fd("RSA key ok\n", args->fd)\
			: error_free_args(INVALID_RSA_KEY, "", args);
}
