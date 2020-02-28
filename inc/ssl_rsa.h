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
void						print_rsa_key(t_args *args, t_buffer key, \
							t_bool is_private, t_bool is_fd_open);
t_uint64					mod_inverse(t_uint64 a, t_uint64 m, \
							t_bool handle_error);
void						get_opts_form(int ac, char **av, t_args *args);
void						get_opts_pass(int ac, char **av, t_args *args);
void						rsa(t_args *args);
void						decode_pem(t_args *args, t_buffer data, \
							t_rsa *rsa_struct);
void						print_rsa_struct_private(t_args *args, \
							t_rsa *rsa_struct);
void						ft_putchar_fd(char c, int fd);
void						ft_putstr_fd(char *s, int fd);
void						ft_putuint64_fd(t_uint64 n, int fd);
void						ft_putuint64_hex_fd(t_uint64 n, t_bool lowercase, \
							int fd);
void						print_rsa_struct_public(t_args *args, \
							t_rsa *rsa_struct);
void						decode_asn1_private(t_args *args, \
							t_rsa *rsa_struct);
void						decode_asn1_public(t_args *args, t_rsa *rsa_struct);
int							uint64_size(t_uint64 n);
void						uint64_to_bytes(t_uint64 n, t_byte *bytes);
void						key_add_uint64(t_uint64 n, t_byte *bytes, \
							int *shift);
t_buffer					rsa_public_key_buffer(t_genrsa genrsa_struct);
void						check_rsa_key(t_args *args, t_rsa *rsa_struct);
t_uint64					gcd(t_uint64 a, t_uint64 b);
t_uint64					lcm(t_uint64 a, t_uint64 b);
t_byte						*rand_bytes(int size);
void						set_data(t_args *args, t_buffer *data);
void						set_fd(t_args *args);
void						get_opts_inkey(int ac, char **av, t_args *args);
void						rsautl(t_args *args);
t_uint64					bytes_to_uint64(t_byte *bytes, int size);
t_uint64					mod_pow(t_uint128 n, t_uint128 p, t_uint128 m);
void						ft_bzero(void *s, size_t n);
void						rsautl_uint64_to_bytes(t_uint64 n, \
							t_byte *bytes);
void						rsautl_uint64_to_bytes(t_uint64 n, \
							t_byte *bytes);
void						print_hexdump(t_buffer buff, int fd);

#endif
