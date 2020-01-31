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

#include "ssl_md5.h"

void						error_rsa(enum e_error e, char *s);
void						get_opts_rsa(char **av, t_args *args, int *i);
t_bool						prime_table_check(t_uint64 n, t_bool print_info);
t_bool						is_prime(t_uint64 n, double p, t_bool print_info);
t_uint64					rand_uint64(t_uint64 min, t_uint64 max);
void						genrsa(void);
void						genrsa_key(t_uint64 p1, t_uint64 p2, t_uint64 e);

#endif
