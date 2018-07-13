/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/16 10:23:50 by rsibiet           #+#    #+#             */
/*   Updated: 2017/05/16 10:23:51 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

# include "../libft/libft.h"
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/mman.h>
# include <stdlib.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>

/*
**	main file
*/
void				otool(char *ptr, int ac, char *av);

/*
**	otool file
*/
void				handle_32(char *ptr);
void				handle_64(char *ptr);

/*
**	print_res file
*/
int					print_otool(uint64_t addr, uint32_t size,
									char *ptr, uint32_t i);
void				print_arch(unsigned int arch, char *av);

/*
**	ft_swap file
*/
uint32_t			ft_swapuint32(uint32_t value);
uint64_t			ft_swapuint64(uint64_t value);
int					get_file_type(uint32_t head);

/*
**	fat_arch file
*/
void				handle_fat_cigam(char *ptr, unsigned int i,
										char *av, char **s);

/*
**	otool_sigam file
*/
void				handle_cigam_32(char *ptr);
void				handle_cigam_64(char *ptr);

#endif
