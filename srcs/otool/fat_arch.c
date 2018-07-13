/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat_arch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/12 14:42:34 by rsibiet           #+#    #+#             */
/*   Updated: 2017/05/12 14:42:36 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>

static int		handle_fat_cigam3(int i, char *ptr)
{
	struct fat_arch			*arch;

	arch = (void *)ptr + sizeof(*(struct fat_header *)ptr);
	while (i > 0)
	{
		if (ft_swapuint32(arch->cputype) == CPU_TYPE_I386)
			return (3);
		arch = (void *)arch + sizeof(*arch);
		--i;
	}
	return (1);
}

static void		handle_fat_cigam2(char *ptr, char *av, int tmp)
{
	struct fat_header		*header;
	struct fat_arch			*arch;
	uint32_t				offset;
	unsigned int			i;

	header = (struct fat_header *)ptr;
	tmp = handle_fat_cigam3(ft_swapuint32(header->nfat_arch), ptr);
	arch = (void *)ptr + sizeof(*header);
	i = ft_swapuint32(header->nfat_arch);
	while (i > 0)
	{
		if (ft_swapuint32(arch->cputype) != CPU_TYPE_I386)
		{
			print_arch(ft_swapuint32(arch->cputype), av);
			offset = ft_swapuint32(arch->offset);
			otool(ptr + offset, -1, av);
		}
		arch = (void *)arch + sizeof(*arch);
		--i;
	}
}

void			handle_fat_cigam(char *ptr, unsigned int i, char *av, char **s)
{
	struct fat_header		*header;
	struct fat_arch			*arch;
	uint32_t				offset;

	header = (struct fat_header *)ptr;
	arch = (void *)ptr + sizeof(*header);
	while (s[i])
	{
		if (s[i + 1] == NULL && ft_strcmp(s[i], "audiodevice") != 0)
		{
			handle_fat_cigam2(ptr, av, 1);
			ft_strdel_del(&s);
			return ;
		}
		++i;
	}
	i = ft_swapuint32(header->nfat_arch);
	while (i-- > 0)
	{
		print_arch(ft_swapuint32(arch->cputype), av);
		offset = ft_swapuint32(arch->offset);
		otool(ptr + offset, -1, av);
		arch = (void *)arch + sizeof(*arch);
	}
	ft_strdel_del(&s);
}
