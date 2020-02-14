/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_md5.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:22:42 by mnguyen           #+#    #+#             */
/*   Updated: 2019/01/14 17:18:43 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SSL_MD5_H
# define SSL_MD5_H

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

# define TRUE				1
# define FALSE				0

typedef unsigned char		t_byte;
typedef unsigned char		t_bool;
typedef unsigned int		t_opts;
typedef unsigned int		t_uint32;
typedef unsigned long int	t_uint64;
typedef long int			t_int64;

enum						e_error
{
	NO_COMMAND = 0,
	INVALID_COMMAND = 1,
	INVALID_OPTS = 2,
	OPT_P_TOO_BIG = 3,
	OPT_S_NO_DATA = 4,
	OPT_S_TOO_BIG = 5,
	FILENAME_TOO_BIG = 6,
	MALLOC_FAILED = 7,
	INVALID_BASE64_OPTS = 8,
	OPT_IO_NO_FILE = 9,
	INVALID_INPUT = 10,
	INVALID_DES_OPTS = 11,
	OPT_KPSV_NO_VALUE = 12,
	OPT_KPSV_TOO_BIG = 13,
	INVALID_HEX = 14,
	INVALID_PASSWORD = 15,
	INVALID_GENRSA_OPTS = 16,
	OPEN_FAILED = 17,
	GENRSA_KEY_GCD_ERROR = 18,
	INVALID_RSA_OPTS = 19,
	INVALID_OPT_FORM = 20,
	OPT_PASS_NO_VALUE = 21,
	OPT_PASS_TOO_BIG = 22,
	INVALID_RSA_INPUT_FILE = 23,
	INVALID_RSA_PEM = 24,
	INVALID_RSA_ASN1 = 25,
	PUBIN_CHECK = 26
};

enum						e_command
{
	MD5 = 0,
	SHA224 = 1,
	SHA256 = 2,
	SHA384 = 3,
	SHA512 = 4,
	BASE64 = 5,
	DES_ECB = 6,
	DES_CBC = 7,
	DES_PCBC = 8,
	DES_CFB = 9,
	DES_OFB = 10,
	DES3_ECB = 11,
	DES3_CBC = 12,
	DES3_PCBC = 13,
	DES3_CFB = 14,
	DES3_OFB = 15,
	GENRSA = 16,
	RSA = 17
};

typedef struct s_buffer		t_buffer;
typedef struct s_disp		t_disp;
typedef struct s_args		t_args;
typedef struct s_md5		t_md5;
typedef struct s_sha256		t_sha256;
typedef struct s_sha512		t_sha512;

# define OPT_P				1
# define OPT_Q				2
# define OPT_R				4
# define OPT_S				8
# define OPT_D				16
# define OPT_I				32
# define OPT_O				64
# define OPT_A				128
# define OPT_K				256
# define OPT_PD				512
# define OPT_SD				1024
# define OPT_V				2048
# define OPT_INF			4096
# define OPT_OUTF			8192
# define OPT_PASSIN			16384
# define OPT_PASSOUT		32768
# define OPT_DES			65536
# define OPT_TEXT			131072
# define OPT_NOOUT			262144
# define OPT_MODULUS		524288
# define OPT_CHECK			1048576
# define OPT_PUBIN			2097152
# define OPT_PUBOUT			4194304
# define OPT_NO				8388608

# define DATA_SIZE_MAX		1048576
# define FILENAME_SIZE_MAX	128

struct						s_buffer
{
	t_byte					*bytes;
	int						size;
};

struct						s_disp
{
	char					*cmd;
	void					*(*set)(t_buffer data);
	void					(*free)(void *hash_struct);
	t_buffer				(*hash)(void *hash_struct);
};

struct						s_md5
{
	t_buffer				data_completed;
	t_buffer				data_out;
	t_uint32				*r;
	t_uint32				*s;
	t_uint32				*w;
	t_uint32				h0;
	t_uint32				h1;
	t_uint32				h2;
	t_uint32				h3;
	t_uint32				a;
	t_uint32				b;
	t_uint32				c;
	t_uint32				d;
	t_uint32				f;
	t_uint32				g;
	t_uint32				tmp;
};

struct						s_sha256
{
	t_buffer				data_completed;
	t_buffer				data_out;
	t_uint32				*k;
	t_uint32				*w;
	t_uint32				h0;
	t_uint32				h1;
	t_uint32				h2;
	t_uint32				h3;
	t_uint32				h4;
	t_uint32				h5;
	t_uint32				h6;
	t_uint32				h7;
	t_uint32				a;
	t_uint32				b;
	t_uint32				c;
	t_uint32				d;
	t_uint32				e;
	t_uint32				f;
	t_uint32				g;
	t_uint32				h;
	t_uint32				t1;
	t_uint32				t2;
};

struct						s_sha512
{
	t_buffer				data_completed;
	t_buffer				data_out;
	t_uint64				*k;
	t_uint64				*w;
	t_uint64				h0;
	t_uint64				h1;
	t_uint64				h2;
	t_uint64				h3;
	t_uint64				h4;
	t_uint64				h5;
	t_uint64				h6;
	t_uint64				h7;
	t_uint64				a;
	t_uint64				b;
	t_uint64				c;
	t_uint64				d;
	t_uint64				e;
	t_uint64				f;
	t_uint64				g;
	t_uint64				h;
	t_uint64				t1;
	t_uint64				t2;
};

struct						s_args
{
	t_disp					disp;
	enum e_command			command;
	t_opts					opts;
	t_buffer				*data;
	int						data_size;
	t_buffer				key;
	t_buffer				password;
	t_buffer				salt;
	t_buffer				iv;
	t_buffer				out_file;
	int						i;
	int						fd;
	int						opt_s_nb;
	t_buffer				passin;
	t_buffer				passout;
};

t_args						get_args(int ac, char **av);
void						get_opts_mdc(char **av, t_args *args, int *i);
void						free_args(t_args *args);
void						error(enum e_error e, char *s);
void						error_free_args(enum e_error e, char *s \
											, t_args *args);
void						exec_files(t_args *args);
void						exec_command(t_args args);
void						set_mem_data(int ac, t_args *args, int *i);
void						*ft_memcpy(void *dest, const void *src, size_t n);
void						*ft_memset(void *s, int c, size_t n);
int							ft_memcmp(const void *s1, const void *s2, size_t n);
int							ft_strlen(char *s);
void						ft_putstr(char *s);
void						ft_putsterr(char *s);
void						ft_putchar(char c);
void						ft_putnbr(int n);
void						print_buffer(t_buffer buf);
void						print_bufferr(t_buffer buf);
void						print_buffer_hex(t_buffer buff);
void						set_dispatcher(t_args *args);
void						*set_md5_struct(t_buffer data);
void						*set_sha224_256_struct(t_buffer data \
													, enum e_command command);
void						*set_sha224_struct(t_buffer data);
void						*set_sha256_struct(t_buffer data);
void						*set_sha384_512_struct(t_buffer data \
													, enum e_command command);
void						*set_sha384_struct(t_buffer data);
void						*set_sha512_struct(t_buffer data);
void						free_md5_struct(void *hash_struct);
void						free_sha256_struct(void *hash_struct);
void						free_sha512_struct(void *hash_struct);
t_uint32					*set_s(t_uint32 *s);
t_uint32					*set_k(t_uint32 *k);
t_uint64					*set_k512(t_uint64 *k);
void						set_w(t_sha256 *sha256_struct, int o);
void						set_w512(t_sha512 *sha512_struct, int o);
void						set_data_out(t_sha256 *sha256_struct \
										, enum e_command command);
void						set_data_out512(t_sha512 *sha512_struct \
											, enum e_command command);
t_buffer					set_data_completed(t_buffer data_completed \
									, t_buffer data, t_bool is_little_endian);
t_buffer					set_data_completed512(t_buffer data_completed \
													, t_buffer data);
t_buffer					md5(void *hash_struct);
t_buffer					sha224_256(void *hash_struct \
										, enum e_command command);
t_buffer					sha224(void *hash_struct);
t_buffer					sha256(void *hash_struct);
t_buffer					sha384_512(void *hash_struct \
										, enum e_command command);
t_buffer					sha384(void *hash_struct);
t_buffer					sha512(void *hash_struct);
t_uint32					right_rotate(t_uint32 value, t_uint32 offset);
t_uint64					right_rotate_long(t_uint64 value, t_uint64 offset);

#endif
