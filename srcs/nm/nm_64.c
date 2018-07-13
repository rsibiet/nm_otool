/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_64.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 16:06:56 by rsibiet           #+#    #+#             */
/*   Updated: 2017/05/11 16:06:58 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

static void		print_output_64(int nsyms, int symoff, int stroff, char *ptr)
{
	int					i;
	char				*stringtable;
	struct nlist_64		*array;
	t_sym				*sym;
	t_param				*param;

	i = 0;
	param = save_param(NULL, 1);
	sym = (t_sym *)ft_memalloc(sizeof(t_sym));
	array = (void *)ptr + symoff;
	stringtable = (void *)ptr + stroff;
	param->head = sym;
	while (i < nsyms)
	{
		sym = new_sym_node(i, NULL, sym);
		sym->name = stringtable + array[i].n_un.n_strx;
		sym->val = ft_itoa_hex(array[i].n_value);
		sym->type = sym_type(array[i].n_type, array[i].n_value,
								array[i].n_sect, '?');
		++i;
	}
	del_bad_node(param->head);
	sort_sym(param->head, NULL, 0);
	print_result(param->head, param->magic_nb);
}

static void		add_sections_64(struct load_command *lc, unsigned int ncmds,
								unsigned int i, unsigned int j)
{
	struct segment_command_64	*seg;
	struct section_64			*sec;
	t_sec						*sec_list;

	while (i < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)lc;
			sec = (struct section_64 *)(seg + sizeof(seg) / sizeof(void *));
			while (j < seg->nsects)
			{
				sec_list = add_sec_node(NULL, sec_list, save_param(NULL, 1),
											sec->sectname);
				sec = (void *)sec + sizeof(struct section_64);
				++j;
			}
			j = 0;
		}
		lc = (void *)lc + lc->cmdsize;
		++i;
	}
}

void			handle_64(char *ptr, unsigned int i)
{
	struct mach_header_64		*header;
	struct load_command			*lc;
	struct symtab_command		*symtab;

	header = (struct mach_header_64 *)ptr;
	if (get_file_type(header->filetype) == -1)
		return ;
	lc = (void *)ptr + sizeof(*header);
	add_sections_64(lc, header->ncmds, 0, 0);
	while (i < header->ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			symtab = (struct symtab_command *)lc;
			print_output_64(symtab->nsyms, symtab->symoff, symtab->stroff, ptr);
			break ;
		}
		lc = (void *)lc + lc->cmdsize;
		++i;
	}
}
