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

#include <nm.h>

void			nm(char *ptr, int ac, char *av)
{
	unsigned int		magic_nb;
	t_param				*param;

	param = (t_param *)ft_memalloc(sizeof(t_param));
	magic_nb = *(unsigned int *)ptr;
	param->magic_nb = magic_nb;
	save_param(param, 0);
	if (ac > 2 && magic_nb != FAT_MAGIC && magic_nb != FAT_CIGAM)
		print_arch(0, av, 2, NULL);
	if (magic_nb == MH_MAGIC_64)
		handle_64(ptr, 0);
	else if (magic_nb == MH_MAGIC)
		handle_32(ptr, 0);
	else if (magic_nb == MH_CIGAM_64)
		handle_cigam_64(ptr, 0);
	else if (magic_nb == MH_CIGAM)
		handle_cigam_32(ptr, 0);
	else
	{
		if (magic_nb == FAT_CIGAM || magic_nb == FAT_MAGIC)
			handle_fat_cigam(ptr, 0, av, ft_strsplit(av, '/'));
		sym_fulldel(param->head, param);
		return ;
	}
	sym_fulldel(param->head, param);
}

void			sort_sym(t_sym *sym, char *tmp, char type)
{
	t_sym	*memo;

	if (save_options(NULL, 1)->p == 1)
		return ;
	while (sym->next)
	{
		memo = sym->next;
		if (sym && sym->name && memo && memo->name &&
			ft_strcmp(sym->name, memo->name) > 0)
		{
			tmp = sym->name;
			sym->name = memo->name;
			memo->name = tmp;
			tmp = sym->val;
			sym->val = memo->val;
			memo->val = tmp;
			type = sym->type;
			sym->type = memo->type;
			memo->type = type;
			sym = save_param(NULL, 1)->head;
		}
		else
			sym = sym->next;
	}
}

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

static void		handle_fat_cigam2(char *ptr, char *av, int tmp, char **s)
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
			if (print_arch(ft_swapuint32(arch->cputype), av, tmp, s) == 1)
				i = 1;
			offset = ft_swapuint32(arch->offset);
			nm(ptr + offset, -1, av);
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
			handle_fat_cigam2(ptr, av, 1, s);
			ft_strdel_del(&s);
			return ;
		}
		++i;
	}
	i = ft_swapuint32(header->nfat_arch);
	while (i-- > 0)
	{
		print_arch(ft_swapuint32(arch->cputype), av, 1, NULL);
		offset = ft_swapuint32(arch->offset);
		nm(ptr + offset, -1, av);
		arch = (void *)arch + sizeof(*arch);
	}
	ft_strdel_del(&s);
}
