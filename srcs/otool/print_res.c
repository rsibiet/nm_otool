/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_res.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 10:40:14 by rsibiet           #+#    #+#             */
/*   Updated: 2017/05/11 10:40:17 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>

static char		*itoa_cig_hex(int val)
{
	int					i;
	char				*c;
	unsigned int		nb;

	i = 1;
	nb = (unsigned int)val;
	if ((c = ft_strnew(3)) == NULL)
		return (NULL);
	while (i >= 0)
	{
		if (nb % 16 < 10)
			c[i] = nb % 16 + '0';
		else
			c[i] = nb % 16 + 'a' - 10;
		nb /= 16;
		i--;
	}
	return (c);
}

static void		print_otool2(uint64_t *addr, uint32_t i, uint32_t j,
								char *itoa)
{
	uint32_t	len;
	char		*str;

	if (i == 9 || i == 17)
		i--;
	if (j % 16 == 0)
	{
		str = ft_itoa_hex(*addr);
		len = ft_strlen(str);
		while (len++ < i)
			ft_putchar('0');
		ft_putstr(str);
		ft_strdel(&str);
		*addr += 16;
		ft_putchar('\t');
	}
	ft_putstr(itoa);
	ft_strdel(&itoa);
}

static int		mod_otool(int i)
{
	if (i == 9 || i == 17)
		return (1);
	return (0);
}

int				print_otool(uint64_t addr, uint32_t size, char *ptr, uint32_t i)
{
	uint32_t	j;
	int			mod;

	j = 0;
	mod = mod_otool(i);
	while (size > j)
	{
		print_otool2(&addr, i, j, itoa_cig_hex(ptr[j]));
		if (mod == 0)
			ft_putchar(' ');
		else
		{
			if (mod == 4)
				ft_putchar(' ');
			if (mod++ == 4)
				mod = 1;
		}
		if ((j + 1) % 16 == 0)
			ft_putchar('\n');
		++j;
	}
	if (j % 16 != 0)
		ft_putchar('\n');
	return (0);
}

void			print_arch(unsigned int arch, char *av)
{
	ft_putstr(av);
	if (arch == CPU_TYPE_POWERPC)
		ft_putstr(" (architecture ppc)");
	else if (arch == CPU_TYPE_POWERPC64)
		ft_putstr(" (architecture ppc64)");
	else if (arch == CPU_TYPE_I860)
		ft_putstr(" (architecture i860)");
	else if (arch == CPU_TYPE_ARM64)
		ft_putstr(" (architecture arm64)");
	else if (arch == CPU_TYPE_ARM)
		ft_putstr(" (architecture arm)");
	else if (arch == CPU_TYPE_I386)
		ft_putstr(" (architecture i386)");
	else if (arch == CPU_TYPE_X86)
		ft_putstr(" (architecture x86)");
	ft_putendl(":");
}
