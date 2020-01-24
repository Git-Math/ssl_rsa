/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_k512.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnguyen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/14 15:18:45 by mnguyen           #+#    #+#             */
/*   Updated: 2019/01/14 17:23:09 by mnguyen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl_md5.h"

void		set_k5120(t_uint64 *k)
{
	k[0] = (t_uint64)(0x428a2f98d728ae22);
	k[1] = (t_uint64)(0x7137449123ef65cd);
	k[2] = (t_uint64)(0xb5c0fbcfec4d3b2f);
	k[3] = (t_uint64)(0xe9b5dba58189dbbc);
	k[4] = (t_uint64)(0x3956c25bf348b538);
	k[5] = (t_uint64)(0x59f111f1b605d019);
	k[6] = (t_uint64)(0x923f82a4af194f9b);
	k[7] = (t_uint64)(0xab1c5ed5da6d8118);
	k[8] = (t_uint64)(0xd807aa98a3030242);
	k[9] = (t_uint64)(0x12835b0145706fbe);
	k[10] = (t_uint64)(0x243185be4ee4b28c);
	k[11] = (t_uint64)(0x550c7dc3d5ffb4e2);
	k[12] = (t_uint64)(0x72be5d74f27b896f);
	k[13] = (t_uint64)(0x80deb1fe3b1696b1);
	k[14] = (t_uint64)(0x9bdc06a725c71235);
	k[15] = (t_uint64)(0xc19bf174cf692694);
	k[16] = (t_uint64)(0xe49b69c19ef14ad2);
	k[17] = (t_uint64)(0xefbe4786384f25e3);
	k[18] = (t_uint64)(0x0fc19dc68b8cd5b5);
	k[19] = (t_uint64)(0x240ca1cc77ac9c65);
	k[20] = (t_uint64)(0x2de92c6f592b0275);
	k[21] = (t_uint64)(0x4a7484aa6ea6e483);
	k[22] = (t_uint64)(0x5cb0a9dcbd41fbd4);
	k[23] = (t_uint64)(0x76f988da831153b5);
	k[24] = (t_uint64)(0x983e5152ee66dfab);
}

void		set_k5121(t_uint64 *k)
{
	k[25] = (t_uint64)(0xa831c66d2db43210);
	k[26] = (t_uint64)(0xb00327c898fb213f);
	k[27] = (t_uint64)(0xbf597fc7beef0ee4);
	k[28] = (t_uint64)(0xc6e00bf33da88fc2);
	k[29] = (t_uint64)(0xd5a79147930aa725);
	k[30] = (t_uint64)(0x06ca6351e003826f);
	k[31] = (t_uint64)(0x142929670a0e6e70);
	k[32] = (t_uint64)(0x27b70a8546d22ffc);
	k[33] = (t_uint64)(0x2e1b21385c26c926);
	k[34] = (t_uint64)(0x4d2c6dfc5ac42aed);
	k[35] = (t_uint64)(0x53380d139d95b3df);
	k[36] = (t_uint64)(0x650a73548baf63de);
	k[37] = (t_uint64)(0x766a0abb3c77b2a8);
	k[38] = (t_uint64)(0x81c2c92e47edaee6);
	k[39] = (t_uint64)(0x92722c851482353b);
	k[40] = (t_uint64)(0xa2bfe8a14cf10364);
	k[41] = (t_uint64)(0xa81a664bbc423001);
	k[42] = (t_uint64)(0xc24b8b70d0f89791);
	k[43] = (t_uint64)(0xc76c51a30654be30);
	k[44] = (t_uint64)(0xd192e819d6ef5218);
	k[45] = (t_uint64)(0xd69906245565a910);
	k[46] = (t_uint64)(0xf40e35855771202a);
	k[47] = (t_uint64)(0x106aa07032bbd1b8);
	k[48] = (t_uint64)(0x19a4c116b8d2d0c8);
	k[49] = (t_uint64)(0x1e376c085141ab53);
}

void		set_k5122(t_uint64 *k)
{
	k[50] = (t_uint64)(0x2748774cdf8eeb99);
	k[51] = (t_uint64)(0x34b0bcb5e19b48a8);
	k[52] = (t_uint64)(0x391c0cb3c5c95a63);
	k[53] = (t_uint64)(0x4ed8aa4ae3418acb);
	k[54] = (t_uint64)(0x5b9cca4f7763e373);
	k[55] = (t_uint64)(0x682e6ff3d6b2b8a3);
	k[56] = (t_uint64)(0x748f82ee5defb2fc);
	k[57] = (t_uint64)(0x78a5636f43172f60);
	k[58] = (t_uint64)(0x84c87814a1f0ab72);
	k[59] = (t_uint64)(0x8cc702081a6439ec);
	k[60] = (t_uint64)(0x90befffa23631e28);
	k[61] = (t_uint64)(0xa4506cebde82bde9);
	k[62] = (t_uint64)(0xbef9a3f7b2c67915);
	k[63] = (t_uint64)(0xc67178f2e372532b);
	k[64] = (t_uint64)(0xca273eceea26619c);
	k[65] = (t_uint64)(0xd186b8c721c0c207);
	k[66] = (t_uint64)(0xeada7dd6cde0eb1e);
	k[67] = (t_uint64)(0xf57d4f7fee6ed178);
	k[68] = (t_uint64)(0x06f067aa72176fba);
	k[69] = (t_uint64)(0x0a637dc5a2c898a6);
	k[70] = (t_uint64)(0x113f9804bef90dae);
	k[71] = (t_uint64)(0x1b710b35131c471b);
	k[72] = (t_uint64)(0x28db77f523047d84);
	k[73] = (t_uint64)(0x32caab7b40c72493);
	k[74] = (t_uint64)(0x3c9ebe0a15c9bebc);
}

void		set_k5123(t_uint64 *k)
{
	k[75] = (t_uint64)(0x431d67c49c100d4c);
	k[76] = (t_uint64)(0x4cc5d4becb3e42b6);
	k[77] = (t_uint64)(0x597f299cfc657e2a);
	k[78] = (t_uint64)(0x5fcb6fab3ad6faec);
	k[79] = (t_uint64)(0x6c44198c4a475817);
}

t_uint64	*set_k512(t_uint64 *k)
{
	k = malloc(sizeof(t_uint64) * 80);
	if (k == NULL)
		error(MALLOC_FAILED, "");
	set_k5120(k);
	set_k5121(k);
	set_k5122(k);
	set_k5123(k);
	return (k);
}
