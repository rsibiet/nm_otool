/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 16:13:53 by rsibiet           #+#    #+#             */
/*   Updated: 2017/05/11 16:13:54 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

static char		sym_section(uint8_t n_sect, t_sec *sec)
{
	while (sec)
	{
		if (sec->nb == n_sect)
		{
			if (ft_strcmp(sec->name, SECT_DATA) == 0)
				return ('D');
			else if (ft_strcmp(sec->name, SECT_BSS) == 0)
				return ('B');
			else if (ft_strcmp(sec->name, SECT_TEXT) == 0)
				return ('T');
			else
				return ('S');
		}
		sec = sec->next;
	}
	return ('S');
}

char			sym_type(uint8_t type, uint64_t value, uint8_t n_sect, char res)
{
	if ((type & N_TYPE) == N_UNDF)
	{
		if (value)
			res = 'C';
		else
			res = 'U';
	}
	else if ((type & N_TYPE) == N_ABS)
		res = 'A';
	else if ((type & N_TYPE) == N_SECT)
		res = sym_section(n_sect, save_param(NULL, 1)->s_head);
	else if ((type & N_TYPE) == N_PBUD)
		res = 'U';
	else if ((type & N_TYPE) == N_INDR)
		res = 'I';
	if ((type & N_STAB) != 0)
		res = 'X';
	if ((type & N_EXT) == 0 && res != '?')
		res = ft_tolower(res);
	return (res);
}
