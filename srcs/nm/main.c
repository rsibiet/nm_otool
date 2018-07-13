/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 10:33:00 by rsibiet           #+#    #+#             */
/*   Updated: 2017/05/11 10:33:02 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

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
	nm(ptr, ac, av);
	if (munmap(ptr, buf.st_size) < 0)
	{
		ft_puterror("munmap failed on ", av);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int		parse_options2(void)
{
	ft_putstr_fd("ft_nm: for the option: may only ", 2);
	ft_putstr_fd("occur zero or one times!\n", 2);
	return (-1);
}

static int		parse_options(char *av, int i, t_opts *opts)
{
	while (av[i])
	{
		if (av[i] == 'g')
			opts->g++;
		else if (av[i] == 'p')
			opts->p++;
		else if (av[i] == 'u')
			opts->u++;
		else if (av[i] == 'U')
			opts->v++;
		else if (av[i] == 'j')
			opts->j++;
		else
		{
			ft_putstr_fd("ft_nm: Unknown command line argument\n", 2);
			return (-1);
		}
		if (opts->g > 1 || opts->p > 1 || opts->u > 1
			|| opts->v > 1 || opts->j > 1)
			return (parse_options2());
		++i;
	}
	return (0);
}

int				main(int ac, char **av)
{
	int			i;
	t_opts		*opts;

	opts = (t_opts *)ft_memalloc(sizeof(t_opts));
	save_options(opts, 0);
	i = 1;
	if (av[1] && av[1][0] == '-')
	{
		if (parse_options(av[1], 1, opts) == -1)
			return (EXIT_FAILURE);
		++i;
	}
	if (i == ac)
		map_file(0, "a.out", NULL, 1);
	while (i < ac)
	{
		if (map_file(0, av[i], NULL, ac) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		++i;
	}
	return (EXIT_SUCCESS);
}
