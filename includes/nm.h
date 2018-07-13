/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 10:23:39 by rsibiet           #+#    #+#             */
/*   Updated: 2017/05/16 10:23:42 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include "../libft/libft.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/mman.h>
# include <stdlib.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>

typedef struct		s_sym
{
	char			*name;
	char			*val;
	char			type;
	struct s_sym	*next;
	struct s_sym	*prev;
}					t_sym;

typedef struct		s_sec
{
	char			*name;
	unsigned int	nb;
	struct s_sec	*next;
}					t_sec;

typedef struct		s_param
{
	t_sym			*head;
	t_sec			*s_head;
	unsigned int	nb_sec;
	unsigned int	magic_nb;
}					t_param;

typedef struct		s_opts
{
	uint8_t			g;
	uint8_t			p;
	uint8_t			u;
	uint8_t			v;
	uint8_t			j;
}					t_opts;

/*
**	main otool file
*/
void				otool(char *ptr, int ac, char *av);

/*
**	nm file
*/
void				handle_32(char *ptr, unsigned int i);
void				handle_64(char *ptr, unsigned int i);

/*
**	print_res file
*/
int					print_arch(unsigned int arch, char *av,
								uint8_t mod, char **s);
void				sort_sym(t_sym *sym, char *tmp, char type);
void				print_result(t_sym *sym, unsigned int magic_number);

/*
**	list file
*/
void				sym_fulldel(t_sym *sym, t_param *param);
void				del_bad_node(t_sym *sym);
t_sym				*new_sym_node(int i, t_sym *new, t_sym *sym);
t_sec				*add_sec_node(t_sec *new, t_sec *sec, t_param *param,
								char *sectname);

/*
**	section file
*/
char				sym_type(uint8_t type, uint64_t value,
								uint8_t n_sect, char res);
/*
**	ft_swap file
*/
uint32_t			ft_swapuint32(uint32_t value);
uint64_t			ft_swapuint64(uint64_t value);
t_param				*save_param(t_param *param, int i);
t_opts				*save_options(t_opts *opts, int i);
int					get_file_type(uint32_t head);

/*
**	fat_arch file
*/
void				nm(char *ptr, int ac, char *av);
void				handle_fat_cigam(char *ptr, unsigned int i,
										char *av, char **s);

/*
**	nm_sigam_32 file
*/
void				handle_cigam_32(char *ptr, unsigned int i);

/*
**	nm_sigam_64 file
*/
void				handle_cigam_64(char *ptr, unsigned int i);

#endif
