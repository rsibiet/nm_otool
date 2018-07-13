/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 16:01:59 by rsibiet           #+#    #+#             */
/*   Updated: 2017/05/15 16:02:02 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <otool.h>

void			otool(char *ptr, int ac, char *av)
{
	unsigned int		magic_nb;

	magic_nb = *(unsigned int *)ptr;
	if (ac != -1 && magic_nb != FAT_CIGAM && magic_nb != FAT_MAGIC)
	{
		ft_putstr(av);
		ft_putendl(":");
	}
	if (magic_nb == MH_MAGIC_64)
		handle_64(ptr);
	else if (magic_nb == MH_MAGIC)
		handle_32(ptr);
	else if (magic_nb == MH_CIGAM_64)
		handle_cigam_64(ptr);
	else if (magic_nb == MH_CIGAM)
		handle_cigam_32(ptr);
	else
	{
		if (magic_nb == FAT_CIGAM || magic_nb == FAT_MAGIC)
			handle_fat_cigam(ptr, 0, av, ft_strsplit(av, '/'));
		return ;
	}
}

static void		ft_puterror(char *str1, char *str2)
{
	ft_putstr_fd(str1, 2);
	ft_putstr_fd(str2, 2);
	ft_putstr_fd(" file\n", 2);
}

static int		map_file(int fd, char *av, char *ptr, int ac)
{
	struct stat		buf;

	if ((fd = open(av, O_RDONLY)) < 0)
	{
		ft_puterror("Failed to open ", av);
		return (EXIT_FAILURE);
	}
	if (fstat(fd, &buf) < 0)
	{
		ft_puterror("fstat failed on ", av);
		return (EXIT_FAILURE);
	}
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
						== MAP_FAILED)
	{
		ft_puterror("mmap failed on ", av);
		return (EXIT_FAILURE);
	}
	otool(ptr, ac, av);
	if (munmap(ptr, buf.st_size) < 0)
	{
		ft_puterror("munmap failed on ", av);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int				main(int ac, char **av)
{
	int		i;

	i = 1;
	if (ac == 1)
	{
		ft_putstr_fd("Missing argument\n", 2);
		return (EXIT_FAILURE);
	}
	while (i < ac)
	{
		if (map_file(0, av[i], NULL, ac) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}
