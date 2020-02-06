/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_des.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:22:42 by mnguyen           #+#    #+#             */
/*   Updated: 2019/01/14 17:18:43 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_DES_H
# define SSL_DES_H

# include "ssl_md5.h"

enum						e_des_mode
{
	ECB = 0,
	CBC = 1,
	PCBC = 2,
	CFB = 3,
	OFB = 4
};

typedef struct s_des		t_des;

struct						s_des
{
	t_buffer				data;
	t_buffer				key;
	t_buffer				iv;
	t_bool					encode;
	t_bool					a;
	t_bool					a3;
	t_bool					padding;
	enum e_des_mode			mode;
	t_buffer				*key_array;
	t_buffer				*data_array;
	int						i;
	int						j;
	t_buffer				f_result;
	t_buffer				block_result;
	t_byte					*input_bytes;
};

void						get_command_des(char **av, t_args *args);
void						get_opts_des(char **av, t_args *args, int *i);
void						get_opts_io(int ac, char **av, t_args *args);
void						get_opts_kpsv(int ac, char **av, t_args *args);
void						set_base64_dispatcher(t_args *args);
void						*set_base64_struct(t_buffer data);
void						free_base64_struct(void *hash_struct);
t_buffer					base64_encode(void *hash_struct);
t_buffer					base64_decode(void *hash_struct);
void						base64_decode_init(t_buffer *result, \
							t_buffer *data);
void						print_buffer_fd(t_buffer buf, int fd);
void						print_base64_buffer(t_args *args, t_buffer buf);
void						print_des_result(t_args *args, t_buffer result);
t_buffer					*remove_data_whitespace(t_buffer *data);
void						error_des(enum e_error e, char *s);
void						set_des_dispatcher(t_args *args);
void						*set_des_struct(t_buffer data);
void						set_des_exclusive(t_args *args, void *hash_struct);
void						free_des_struct(void *hash_struct);
t_buffer					des(void *hash_struct);
t_buffer					des3(void *hash_struct);
void						pbkdf(t_args *args, t_des *des_struct);
t_buffer					buffer_hex_to_byte(t_args *args, t_buffer hex_buf, \
							int size);
t_buffer					des_permutation(t_byte *data, int *table, \
							int table_size);
t_buffer					des_left_rotate(t_buffer key, int shift_nb);
void						des_xor(t_byte *dest, t_byte *other, int size);
void						des_reverse(t_buffer buff);
void						des_fp_mode(t_des *des_struct, t_buffer *result);
t_buffer					*des_key_setup(t_buffer key);
void						f_set_s(t_buffer *s, t_buffer e);
t_buffer					f(t_buffer *data_array, t_buffer *key_array, \
							int j, t_des *des_struct);
t_buffer					data_setup(t_des *des_struct);
t_buffer					result_finalize(t_buffer result, t_des *des_struct);
void						des_ip(t_des *des_struct, t_buffer *result);
void						des_fp_mode(t_des *des_struct, t_buffer *result);
void						des_fp(t_des *des_struct, t_buffer *result);
void						print_base64_encode_buffer0(t_args *args, \
							t_buffer buf);

#endif
