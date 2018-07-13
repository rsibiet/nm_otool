/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 16:21:52 by rsibiet           #+#    #+#             */
/*   Updated: 2017/05/11 16:21:54 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

uint32_t	ft_swapuint32(uint32_t value)
{
	value = (((value << 24) | ((value << 8) & 0x00FF0000)) | (((value >> 8)
				& 0x0000FF00) | (value >> 24)));
	return (value);
}

uint64_t	ft_swapuint64(uint64_t val)
{
	val = ((val << 8) & 0xFF00FF00FF00FF00ULL) | ((val >> 8)
				& 0x00FF00FF00FF00FFULL);
	val = ((val << 16) & 0xFFFF0000FFFF0000ULL) | ((val >> 16)
				& 0x0000FFFF0000FFFFULL);
	return ((val << 32) | (val >> 32));
}

t_opts		*save_options(t_opts *opts, int i)
{
	static t_opts		*tp = NULL;

	if (i == 0)
		tp = opts;
	return (tp);
}

t_param		*save_param(t_param *param, int i)
{
	static t_param		*tp = NULL;

	if (i == 0)
		tp = param;
	return (tp);
}

int			get_file_type(uint32_t filetype)
{
	if (filetype == MH_OBJECT || filetype == MH_EXECUTE
		|| filetype == MH_FVMLIB || filetype == MH_CORE
		|| filetype == MH_PRELOAD || filetype == MH_DYLIB
		|| filetype == MH_DYLINKER || filetype == MH_BUNDLE
		|| filetype == MH_DYLIB_STUB)
		return (0);
	return (-1);
}
