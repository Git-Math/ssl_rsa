/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genrsa.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/24 17:18:56 by mnguyen           #+#    #+#             */
/*   Updated: 2020/01/24 17:18:57 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_rsa.h"

t_uint64	bytes_to_uint64(t_byte *bytes)
{
	t_uint64	n;
	int			i;

	n = 0;
	i = 0;
	while (i < 8)
	{
		n += (t_uint64)(bytes[i] << (i * 8));
		i++;
	}
	return (n);
}

t_uint64	rand_uint64(t_uint64 min, t_uint64 max)
{
    t_byte		*rand_bytes;
	t_uint64	rand_n;
	int			fd;

	rand_bytes = (t_byte *)malloc(sizeof(t_byte) * 8);
	(rand_bytes == NULL) ? error(MALLOC_FAILED, "") : 0;
	fd = open("/dev/urandom", O_RDONLY);
	(fd < 0) ? error(OPEN_FAILED, "") : 0;
	read(fd, rand_bytes, 8);
	rand_n = bytes_to_uint64(rand_bytes);
	rand_n = (rand_n % (max - min + 1)) + min;
    close(fd);
	free(rand_bytes);
    return (rand_n);
}

t_uint64	gen_prime(void)
{
	t_uint64	n;
	t_uint64	n_safe;
	t_bool		prime_found;

	prime_found = FALSE;
	while (!prime_found)
	{
		n = rand_uint64(3037000500, 4294967295);
		n_safe = (n - 1) / 2;
		if (!prime_table_check(n_safe, FALSE))
			continue;
		if (!is_prime(n_safe, 0.9999999999999999, FALSE))
			continue;
		if (!prime_table_check(n, TRUE))
			continue;
		if (is_prime(n, 0.9999999999999999, TRUE))
			prime_found = TRUE;
	}
	return (n);
}

t_buffer	genrsa(void)
{
	t_genrsa	genrsa_struct;

	ft_putstr("Generating RSA private key, 64 bit long modulus\n");
	genrsa_struct.p = gen_prime();
	ft_putchar('\n');
	genrsa_struct.q = genrsa_struct.p;
	while (genrsa_struct.q == genrsa_struct.p)
		genrsa_struct.q = gen_prime();
	ft_putchar('\n');
	genrsa_struct.e = 65537;
	ft_putstr("e is 65537 (0x10001)\n");
	return (genrsa_key(genrsa_struct));
}
