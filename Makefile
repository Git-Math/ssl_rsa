#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/12/12 18:52:41 by mnguyen           #+#    #+#              #
#    Updated: 2018/12/12 18:52:46 by mnguyen          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_ssl

SRC = main.c exec_command.c md5.c print.c set_md5_struct.c	\
		sha256.c error.c exec_files.c get_args.c print0.c	\
		set_k.c set_s.c sha256_struct.c mem.c sha512.c		\
		set_k512.c sha512_struct.c dispatcher.c				\
		sha224_256.c sha384_512.c							\
		base64.c print_base64.c get_args_des.c				\
		dispatcher_des.c set_base64_struct.c error_des.c	\
		des.c get_opts_mdc.c get_opts_kpsv.c                \
        set_des_struct.c des3.c pbkdf.c command.c base640.c	\
		des_binary.c des_tools.c des_ifp.c					\
		is_prime.c dispatcher_rsa.c genrsa.c error_rsa.c	\
		get_args_rsa.c genrsa_key.c genrsa_key_buffer.c		\
		print_rsa_key.c get_opts_rsa.c rsa.c decode_pem.c	\
		print_rsa.c decode_asn1.c check_rsa_key.c rsautl.c	\
		rsautl_util.c gendsa.c gendes.c break_rsa.c			\
		hash_table.c

OBJ = $(SRC:.c=.o)

SRCDIR = ./src/

OBJDIR = ./obj/

SRCS = $(addprefix $(SRCDIR), $(SRC))

OBJS = $(addprefix $(OBJDIR), $(OBJ))

CC = gcc

FLAGS = -Wall -Werror -Wextra

INCLUDES = -I ./inc

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $(NAME) $(OBJS)

$(OBJS): $(SRCS)
	rm -rf $(OBJDIR)
	mkdir $(OBJDIR)
	$(CC) $(FLAGS) $(INCLUDES) -c $(SRCS)
	mv $(OBJ) $(OBJDIR)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
