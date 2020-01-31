/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 00:41:30 by mnguyen           #+#    #+#             */
/*   Updated: 2019/11/07 00:41:31 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_md5.h"
#include "ssl_des.h"

void	get_command_rsa(char **av, t_args *args)
{
	if (ft_strlen(av[1]) == 6 && !ft_memcmp(av[1], "genrsa", 6))
		args->command = GENRSA;
	else
		error(INVALID_COMMAND, av[1]);
}

void	get_command_des(char **av, t_args *args)
{
	if (ft_strlen(av[1]) == 7 && !ft_memcmp(av[1], "des-ecb", 7))
		args->command = DES_ECB;
	else if ((ft_strlen(av[1]) == 7 && !ft_memcmp(av[1], "des-cbc", 7))\
				|| (ft_strlen(av[1]) == 3 && !ft_memcmp(av[1], "des", 3)))
		args->command = DES_CBC;
	else if (ft_strlen(av[1]) == 8 && !ft_memcmp(av[1], "des-pcbc", 8))
		args->command = DES_PCBC;
	else if (ft_strlen(av[1]) == 7 && !ft_memcmp(av[1], "des-cfb", 7))
		args->command = DES_CFB;
	else if (ft_strlen(av[1]) == 7 && !ft_memcmp(av[1], "des-ofb", 7))
		args->command = DES_OFB;
	else if (ft_strlen(av[1]) == 8 && !ft_memcmp(av[1], "des3-ecb", 8))
		args->command = DES3_ECB;
	else if ((ft_strlen(av[1]) == 8 && !ft_memcmp(av[1], "des3-cbc", 8))\
		|| (ft_strlen(av[1]) == 4 && !ft_memcmp(av[1], "des3", 4)))
		args->command = DES3_CBC;
	else if (ft_strlen(av[1]) == 9 && !ft_memcmp(av[1], "des3-pcbc", 9))
		args->command = DES3_PCBC;
	else if (ft_strlen(av[1]) == 8 && !ft_memcmp(av[1], "des3-cfb", 8))
		args->command = DES3_CFB;
	else if (ft_strlen(av[1]) == 8 && !ft_memcmp(av[1], "des3-ofb", 8))
		args->command = DES3_OFB;
	else
		get_command_rsa(av, args);
}
