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

#include <nm.h>

static int		print_arch2(char *av, uint8_t mod, char **s)
{
	int		i;

	i = 0;
	while (s && s[i])
	{
		if (s[i + 1] == NULL && (ft_strcmp(s[i], "sqlite3") == 0
			|| ft_strcmp(s[i], "uuidgen") == 0
			|| ft_strcmp(s[i], "appsleepd") == 0
			|| ft_strcmp(s[i], "distnoted") == 0
			|| ft_strcmp(s[i], "pboard") == 0
			|| ft_strcmp(s[i], "cfprefsd") == 0))
			return (0);
		++i;
	}
	if (mod == 3)
		return (0);
	ft_putchar('\n');
	ft_putstr(av);
	if (mod == 2)
	{
		ft_putendl(":");
		return (0);
	}
	return (1);
}

int				print_arch(unsigned int arch, char *av, uint8_t mod, char **s)
{
	int		ret;

	ret = print_arch2(av, mod, s);
	if (arch == CPU_TYPE_POWERPC)
		ft_putstr(" (for architecture ppc)");
	else if (arch == CPU_TYPE_POWERPC64)
		ft_putstr(" (for architecture ppc64)");
	else if (arch == CPU_TYPE_I860)
		ft_putstr(" (for architecture i860)");
	else if (arch == CPU_TYPE_ARM64)
		ft_putstr(" (for architecture arm64)");
	else if (arch == CPU_TYPE_ARM)
		ft_putstr(" (for architecture arm)");
	else if (arch == CPU_TYPE_I386)
		ft_putstr(" (for architecture i386)");
	else if (arch == CPU_TYPE_X86)
		ft_putstr(" (for architecture x86)");
	if (ret == 1)
	{
		ft_putendl(":");
		return (0);
	}
	return (1);
}

static void		print_sym_value(char *s, char type, int len)
{
	int			nb;
	char		c;

	nb = ft_strlen(s);
	c = '0';
	if (nb == 1 && type == 'U')
		c = ' ';
	while (nb < len)
	{
		ft_putchar(c);
		++nb;
	}
	if (c == ' ')
		ft_putchar(c);
	else
		ft_putstr(s);
}

static void		print_result2(t_sym *sym, unsigned int magic_number)
{
	if (magic_number == MH_MAGIC_64)
		print_sym_value(sym->val, sym->type, 16);
	else
		print_sym_value(sym->val, sym->type, 8);
	ft_putchar(' ');
	ft_putchar(sym->type);
	ft_putchar(' ');
	ft_putendl(sym->name);
}

void			print_result(t_sym *sym, unsigned int magic_number)
{
	t_opts		*op;

	op = save_options(NULL, 1);
	while (sym != NULL)
	{
		if ((op->g == 1 && sym->type > 96) || (op->u == 1 && sym->type != 'c'
			&& sym->type != 'u' && sym->type != 'C' && sym->type != 'U')
			|| (op->v == 1 && (sym->type == 'c' || sym->type == 'u'
			|| sym->type == 'C' || sym->type == 'U')))
		{
			sym = sym->next;
			continue ;
		}
		if ((op->u == 1 && (sym->type == 'c' || sym->type == 'u'
			|| sym->type == 'C' || sym->type == 'U')) || op->j == 1)
		{
			ft_putendl(sym->name);
			sym = sym->next;
			continue ;
		}
		print_result2(sym, magic_number);
		sym = sym->next;
	}
}
