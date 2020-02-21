/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_rsa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 17:48:17 by mnguyen           #+#    #+#             */
/*   Updated: 2020/02/14 17:48:18 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_rsa.h"

void	ft_putuint64_fd(t_uint64 n, int fd)
{
	if (n == 0)
		ft_putchar_fd('0', fd);
	else
	{
		if (n / 10 > 0)
			ft_putuint64_fd(n / 10, fd);
		ft_putchar_fd(n % 10 + '0', fd);
	}
}

void	ft_putuint64_hex_fd(t_uint64 n, t_bool lowercase, int fd)
{
	if (n == 0)
		ft_putchar_fd('0', fd);
	else
	{
		if (n / 16 > 0)
			ft_putuint64_hex_fd(n / 16, lowercase, fd);
		if ((n % 16) < 10)
			ft_putuint64_fd(n % 16, fd);
		else
			ft_putchar_fd((n % 16) - 10 + (lowercase ? 'a' : 'A'), fd);
	}
}

void	print_rsa_struct_private0(t_args *args, t_rsa *rsa_struct)
{
	ft_putstr_fd(")\nprime2: ", args->fd);
	ft_putuint64_fd(rsa_struct->q, args->fd);
	ft_putstr_fd(" (0x", args->fd);
	ft_putuint64_hex_fd(rsa_struct->q, TRUE, args->fd);
	ft_putstr_fd(")\nexponent1: ", args->fd);
	ft_putuint64_fd(rsa_struct->exp1, args->fd);
	ft_putstr_fd(" (0x", args->fd);
	ft_putuint64_hex_fd(rsa_struct->exp1, TRUE, args->fd);
	ft_putstr_fd(")\nexponent2: ", args->fd);
	ft_putuint64_fd(rsa_struct->exp2, args->fd);
	ft_putstr_fd(" (0x", args->fd);
	ft_putuint64_hex_fd(rsa_struct->exp2, TRUE, args->fd);
	ft_putstr_fd(")\ncoefficient: ", args->fd);
	ft_putuint64_fd(rsa_struct->coef, args->fd);
	ft_putstr_fd(" (0x", args->fd);
	ft_putuint64_hex_fd(rsa_struct->coef, TRUE, args->fd);
	ft_putstr_fd(")\n", args->fd);
}

void	print_rsa_struct_private(t_args *args, t_rsa *rsa_struct)
{
	ft_putstr_fd("Private-Key: (64 bit)\nmodulus: ", args->fd);
	ft_putuint64_fd(rsa_struct->n, args->fd);
	ft_putstr_fd(" (0x", args->fd);
	ft_putuint64_hex_fd(rsa_struct->n, TRUE, args->fd);
	ft_putstr_fd(")\npublicExponent: ", args->fd);
	ft_putuint64_fd(rsa_struct->e, args->fd);
	ft_putstr_fd(" (0x", args->fd);
	ft_putuint64_hex_fd(rsa_struct->e, TRUE, args->fd);
	ft_putstr_fd(")\nprivateExponent: ", args->fd);
	ft_putuint64_fd(rsa_struct->d, args->fd);
	ft_putstr_fd(" (0x", args->fd);
	ft_putuint64_hex_fd(rsa_struct->d, TRUE, args->fd);
	ft_putstr_fd(")\nprime1: ", args->fd);
	ft_putuint64_fd(rsa_struct->p, args->fd);
	ft_putstr_fd(" (0x", args->fd);
	ft_putuint64_hex_fd(rsa_struct->p, TRUE, args->fd);
	print_rsa_struct_private0(args, rsa_struct);
}

void	print_rsa_struct_public(t_args *args, t_rsa *rsa_struct)
{
	ft_putstr_fd("Public-Key: (64 bit)\nModulus: ", args->fd);
	ft_putuint64_fd(rsa_struct->n, args->fd);
	ft_putstr_fd(" (0x", args->fd);
	ft_putuint64_hex_fd(rsa_struct->n, TRUE, args->fd);
	ft_putstr_fd(")\nExponent: ", args->fd);
	ft_putuint64_fd(rsa_struct->e, args->fd);
	ft_putstr_fd(" (0x", args->fd);
	ft_putuint64_hex_fd(rsa_struct->e, TRUE, args->fd);
	ft_putstr_fd(")\n", args->fd);
}
