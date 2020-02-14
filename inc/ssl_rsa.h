/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_rsa.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 16:41:02 by mnguyen           #+#    #+#             */
/*   Updated: 2020/01/23 16:41:03 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_RSA_H
# define SSL_RSA_H

# include "ssl_md5.h"

typedef struct s_genrsa		t_genrsa;
typedef struct s_rsa		t_rsa;

struct						s_genrsa
{
	t_uint64				n;
	t_uint64				e;
	t_uint64				d;
	t_uint64				p;
	t_uint64				q;
	t_uint64				l;
};

struct						s_rsa
{
	t_buffer				asn164;
	t_buffer				asn1;
	t_uint64				n;
	t_uint64				e;
	t_uint64				d;
	t_uint64				p;
	t_uint64				q;
	t_uint64				exp1;
	t_uint64				exp2;
	t_uint64				coef;
};

void						error_rsa(enum e_error e, char *s);
void						get_opts_rsa(char **av, t_args *args, int *i);
t_bool						prime_table_check(t_uint64 n, t_bool print_info);
t_bool						is_prime(t_uint64 n, double p, t_bool print_info);
t_uint64					rand_uint64(t_uint64 min, t_uint64 max);
t_buffer					genrsa(void);
t_buffer					genrsa_key(t_genrsa genrsa_struct);
t_buffer					genrsa_key_buffer(t_genrsa genrsa_struct);
void						print_rsa_key(t_args *args, t_buffer key);
t_uint64					mod_inverse(t_uint64 a, t_uint64 m);
void						get_opts_form(int ac, char **av, t_args *args);
void						get_opts_pass(int ac, char **av, t_args *args);
void						rsa(t_args *args);
void						decode_pem(t_args *args, t_buffer data, \
							t_rsa *rsa_struct);
void						print_rsa_struct_private(t_args *args, \
							t_rsa *rsa_struct);
void						ft_putchar_fd(char c, int fd);
void						ft_putstr_fd(char *s, int fd);
void						ft_putuint64_hex_fd(t_uint64 n, t_bool lowercase, \
							int fd);
void						print_rsa_struct_public(t_args *args, \
							t_rsa *rsa_struct);

#endif
