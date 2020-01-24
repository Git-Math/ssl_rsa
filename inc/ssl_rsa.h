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

t_bool						is_prime(t_uint64 n, double p);
t_uint64					rand_uint64(t_uint64 min, t_uint64 max); //TEMP remove ?

#endif
