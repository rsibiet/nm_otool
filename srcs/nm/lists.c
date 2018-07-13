/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/11 14:49:28 by rsibiet           #+#    #+#             */
/*   Updated: 2017/05/11 14:49:32 by rsibiet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <nm.h>

static void		sym_delone(t_sym **sym, t_sym *node)
{
	if (!node)
		return ;
	if (sym && *sym)
		*sym = node->next;
	ft_bzero(node, sizeof(t_sym));
	ft_memdel((void **)&node);
}

void			sym_fulldel(t_sym *sym, t_param *param)
{
	while (sym != NULL)
		sym_delone(&sym, sym);
	ft_bzero(param, sizeof(t_param));
	ft_memdel((void **)&param);
}

void			del_bad_node(t_sym *sym)
{
	t_sym	*memo;

	while (sym)
	{
		if (sym->type == 'X' || sym->type == 'x')
		{
			if (sym->prev)
				sym->prev->next = sym->next;
			else
				save_param(NULL, 1)->head = sym->next;
			if (sym->next)
				sym->next->prev = sym->prev;
			free(sym->val);
			sym->type = 0;
			sym->name = NULL;
			memo = sym->next;
			free(sym);
			sym = memo;
		}
		else
			sym = sym->next;
	}
}

t_sym			*new_sym_node(int i, t_sym *new, t_sym *sym)
{
	if (i == 0)
		return (sym);
	new = (t_sym *)ft_memalloc(sizeof(t_sym));
	sym->next = new;
	new->prev = sym;
	return (new);
}

t_sec			*add_sec_node(t_sec *new, t_sec *sec, t_param *param,
								char *sectname)
{
	new = (t_sec *)ft_memalloc(sizeof(t_sec));
	if (param->s_head == NULL)
		param->s_head = new;
	else
		sec->next = new;
	new->name = ft_strdup(sectname);
	param->nb_sec += 1;
	new->nb = param->nb_sec;
	return (new);
}
