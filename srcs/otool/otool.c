/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 13:43:26 by rsibiet           #+#    #+#             */
/*   Updated: 2017/05/16 13:43:27 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>

static int		add_sections_64(struct load_command *lc, unsigned int ncmds,
								unsigned int i, char *ptr)
{
	struct segment_command_64	*seg;
	struct section_64			*sec;
	unsigned int				j;

	j = 0;
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)lc;
			sec = (struct section_64 *)(seg + sizeof(seg) / sizeof(void *));
			while (j < seg->nsects)
			{
				if (ft_strcmp(sec->sectname, "__text") == 0
					&& ft_strcmp(sec->segname, "__TEXT") == 0)
					return (print_otool(sec->addr, sec->size,
									ptr + sec->offset, 16));
					sec = (void *)sec + sizeof(struct section_64);
				++j;
			}
			j = 0;
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return (0);
}

void			handle_64(char *ptr)
{
	struct mach_header_64		*header;
	struct load_command			*lc;

	header = (struct mach_header_64 *)ptr;
	if (get_file_type(header->filetype) == -1)
		return ;
	lc = (void *)ptr + sizeof(*header);
	ft_putendl("Contents of (__TEXT,__text) section");
	add_sections_64(lc, header->ncmds, 0, ptr);
}

static int		add_sections_32(struct load_command *lc, unsigned int ncmds,
								unsigned int i, char *ptr)
{
	struct segment_command	*seg;
	struct section			*sec;
	unsigned int			j;

	j = 0;
	while (i++ < ncmds)
	{
		if (lc->cmd == LC_SEGMENT)
		{
			seg = (struct segment_command *)lc;
			sec = (struct section *)(seg + sizeof(seg) / sizeof(void *));
			while (j < seg->nsects)
			{
				if (ft_strcmp(sec->sectname, "__text") == 0
					&& ft_strcmp(sec->segname, "__TEXT") == 0)
					return (print_otool(sec->addr, sec->size,
									ptr + sec->offset, 8));
					sec = (void *)sec + sizeof(struct section);
				++j;
			}
			j = 0;
		}
		lc = (void *)lc + lc->cmdsize;
	}
	return (0);
}

void			handle_32(char *ptr)
{
	struct mach_header			*header;
	struct load_command			*lc;

	header = (struct mach_header *)ptr;
	if (get_file_type(header->filetype) == -1)
		return ;
	lc = (void *)ptr + sizeof(*header);
	ft_putendl("Contents of (__TEXT,__text) section");
	add_sections_32(lc, header->ncmds, 0, ptr);
}
