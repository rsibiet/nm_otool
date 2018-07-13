/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_addr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 15:10:15 by rsibiet           #+#    #+#             */
/*   Updated: 2017/05/16 15:10:17 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static uint64_t	pow_16(size_t pw)
{
	uint64_t	to_return;
	size_t		i;

	i = 0;
	to_return = 1;
	while (i < pw && to_return <= 1152921504606846976)
	{
		to_return = to_return * 16;
		++i;
	}
	return (to_return);
}

static char		get_char(unsigned char digit, int is_upcase)
{
	if (digit <= 9)
		return (digit + '0');
	digit -= 10;
	if (is_upcase)
		return (digit + 'A');
	else
		return (digit + 'a');
}

static void		print_num(size_t num_digit, uint64_t n,
						char *to_return, int is_upcase)
{
	size_t			i;
	size_t			istr;
	unsigned char	digit;

	i = num_digit;
	istr = 0;
	while (i > 0)
	{
		digit = n / pow_16(i - 1);
		n = n % pow_16(i - 1);
		to_return[istr] = get_char(digit, is_upcase);
		++istr;
		--i;
	}
	to_return[num_digit] = '\0';
}

void			ft_itoa_hex2(uint64_t n, int is_upcase, char *buff)
{
	size_t		digit;
	uint64_t	nb;

	digit = 1;
	nb = n;
	if (n > 1152921504606846976)
		digit = 15;
	else
	{
		while (pow_16(digit) <= nb)
			++digit;
	}
	print_num(digit, nb, buff, is_upcase);
}

void			ft_put_addr(void *addr)
{
	char	buff[20];

	ft_itoa_hex2((uint64_t)addr, 1, buff);
	ft_putstr("0x");
	ft_putstr(buff);
}
