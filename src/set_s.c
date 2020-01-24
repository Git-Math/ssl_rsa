/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_s.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 14:51:11 by mnguyen           #+#    #+#             */
/*   Updated: 2019/01/14 17:21:19 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_md5.h"

void		set_s0(t_uint32 *s)
{
	s[0] = 0xd76aa478;
	s[1] = 0xe8c7b756;
	s[2] = 0x242070db;
	s[3] = 0xc1bdceee;
	s[4] = 0xf57c0faf;
	s[5] = 0x4787c62a;
	s[6] = 0xa8304613;
	s[7] = 0xfd469501;
	s[8] = 0x698098d8;
	s[9] = 0x8b44f7af;
	s[10] = 0xffff5bb1;
	s[11] = 0x895cd7be;
	s[12] = 0x6b901122;
	s[13] = 0xfd987193;
	s[14] = 0xa679438e;
	s[15] = 0x49b40821;
	s[16] = 0xf61e2562;
	s[17] = 0xc040b340;
	s[18] = 0x265e5a51;
	s[19] = 0xe9b6c7aa;
	s[20] = 0xd62f105d;
	s[21] = 0x02441453;
	s[22] = 0xd8a1e681;
	s[23] = 0xe7d3fbc8;
}

void		set_s1(t_uint32 *s)
{
	s[24] = 0x21e1cde6;
	s[25] = 0xc33707d6;
	s[26] = 0xf4d50d87;
	s[27] = 0x455a14ed;
	s[28] = 0xa9e3e905;
	s[29] = 0xfcefa3f8;
	s[30] = 0x676f02d9;
	s[31] = 0x8d2a4c8a;
	s[32] = 0xfffa3942;
	s[33] = 0x8771f681;
	s[34] = 0x6d9d6122;
	s[35] = 0xfde5380c;
	s[36] = 0xa4beea44;
	s[37] = 0x4bdecfa9;
	s[38] = 0xf6bb4b60;
	s[39] = 0xbebfbc70;
	s[40] = 0x289b7ec6;
	s[41] = 0xeaa127fa;
	s[42] = 0xd4ef3085;
	s[43] = 0x04881d05;
	s[44] = 0xd9d4d039;
	s[45] = 0xe6db99e5;
	s[46] = 0x1fa27cf8;
	s[47] = 0xc4ac5665;
}

void		set_s2(t_uint32 *s)
{
	s[48] = 0xf4292244;
	s[49] = 0x432aff97;
	s[50] = 0xab9423a7;
	s[51] = 0xfc93a039;
	s[52] = 0x655b59c3;
	s[53] = 0x8f0ccc92;
	s[54] = 0xffeff47d;
	s[55] = 0x85845dd1;
	s[56] = 0x6fa87e4f;
	s[57] = 0xfe2ce6e0;
	s[58] = 0xa3014314;
	s[59] = 0x4e0811a1;
	s[60] = 0xf7537e82;
	s[61] = 0xbd3af235;
	s[62] = 0x2ad7d2bb;
	s[63] = 0xeb86d391;
}

t_uint32	*set_s(t_uint32 *s)
{
	s = malloc(sizeof(t_uint32) * 64);
	if (s == NULL)
		error(MALLOC_FAILED, "");
	set_s0(s);
	set_s1(s);
	set_s2(s);
	return (s);
}
