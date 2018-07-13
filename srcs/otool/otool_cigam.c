/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_cigam.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 13:43:34 by rsibiet           #+#    #+#             */
/*   Updated: 2017/05/16 13:43:36 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>

static int		add_sections_cigam_64(struct load_command *lc,
					unsigned int ncmds, unsigned int i, char *ptr)
{
	struct segment_command_64	*seg;
	struct section_64			*sec;
	unsigned int				j;

	j = 0;
	while (i++ < ncmds)
	{
		if (ft_swapuint32(lc->cmd) == LC_SEGMENT_64)
		{
			seg = (struct segment_command_64 *)lc;
			sec = (struct section_64 *)(seg + sizeof(seg) / sizeof(void *));
			while (j++ < ft_swapuint32(seg->nsects))
			{
				if (ft_strcmp(sec->sectname, "__text") == 0
					&& ft_strcmp(sec->segname, "__TEXT") == 0)
					return (print_otool(ft_swapuint32(sec->addr),
						ft_swapuint32(sec->size),
						ptr + ft_swapuint32(sec->offset), 17));
					sec = (void *)sec + sizeof(struct section_64);
			}
			j = 0;
		}
		lc = (void *)lc + ft_swapuint32(lc->cmdsize);
	}
	return (0);
}

void			handle_cigam_64(char *ptr)
{
	struct mach_header_64		*header;
	struct load_command			*lc;

	header = (struct mach_header_64 *)ptr;
	if (get_file_type(ft_swapuint32(header->filetype)) == -1)
		return ;
	lc = (void *)ptr + sizeof(*header);
	ft_putendl("Contents of (__TEXT,__text) section");
	add_sections_cigam_64(lc, header->ncmds, 0, ptr);
}

static int		add_sections_cigam_32(struct load_command *lc,
					unsigned int ncmds, unsigned int i, char *ptr)
{
	struct segment_command	*seg;
	struct section			*sec;
	unsigned int			j;

	j = 0;
	while (i++ < ncmds)
	{
		if (ft_swapuint32(lc->cmd) == LC_SEGMENT)
		{
			seg = (struct segment_command *)lc;
			sec = (struct section *)(seg + sizeof(seg) / sizeof(void *));
			while (j++ < ft_swapuint32(seg->nsects))
			{
				if (ft_strcmp(sec->sectname, "__text") == 0
					&& ft_strcmp(sec->segname, "__TEXT") == 0)
					return (print_otool(ft_swapuint32(sec->addr),
						ft_swapuint32(sec->size),
						ptr + ft_swapuint32(sec->offset), 9));
					sec = (void *)sec + sizeof(struct section);
			}
			j = 0;
		}
		lc = (void *)lc + ft_swapuint32(lc->cmdsize);
	}
	return (0);
}

void			handle_cigam_32(char *ptr)
{
	struct mach_header			*header;
	struct load_command			*lc;

	header = (struct mach_header *)ptr;
	if (get_file_type(ft_swapuint32(header->filetype)) == -1)
		return ;
	lc = (void *)ptr + sizeof(*header);
	ft_putendl("Contents of (__TEXT,__text) section");
	add_sections_cigam_32(lc, header->ncmds, 0, ptr);
}
