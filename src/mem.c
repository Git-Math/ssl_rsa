/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:48:19 by mnguyen           #+#    #+#             */
/*   Updated: 2019/01/14 14:49:20 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_md5.h"

void	set_mem_data(int ac, t_args *args, int *i)
{
	if (args->command == GENRSA || args->command == GENDSA \
								|| args->command == GENDES)
		return ;
	args->data_size = ac - *i + args->opt_s_nb;
	if (args->opts & OPT_P || args->opts & OPT_NO || args->command >= BASE64)
		args->data_size++;
	args->data = malloc(sizeof(t_buffer) * args->data_size);
	if (args->data == NULL)
		error(MALLOC_FAILED, "");
	if (args->opts & OPT_P || args->opts & OPT_NO)
	{
		args->data[args->i].bytes = malloc(sizeof(unsigned char) \
											* (DATA_SIZE_MAX + 1));
		if (args->data[args->i].bytes == NULL)
			error(MALLOC_FAILED, "");
		usleep(200 * 1000);
		args->data[args->i].size = read(0, args->data[args->i].bytes \
										, DATA_SIZE_MAX + 1);
		if (args->data[args->i].size > DATA_SIZE_MAX)
			error_free_args(OPT_P_TOO_BIG, "", args);
		args->i++;
	}
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = dest;
	s = src;
	if (dest != src)
		while (n--)
			*d++ = *s++;
	return (dest);
}

void	*ft_memset(void *s, int c, size_t n)
{
	char *swap;

	if (n)
	{
		swap = s;
		while (n--)
			*swap++ = (char)c;
	}
	return (s);
}

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*str1;
	const unsigned char	*str2;

	if (s1 != s2 && n)
	{
		str1 = (const unsigned char *)s1;
		str2 = (const unsigned char *)s2;
		while (n--)
		{
			if (*str1 != *str2)
				return (*str1 - *str2);
			str1++;
			str2++;
		}
	}
	return (0);
}

void	ft_bzero(void *s, size_t n)
{
	while (n > 0)
		((t_byte *)s)[(n--) - 1] = 0;
}
