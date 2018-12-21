/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 14:34:48 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/21 12:41:03 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_flist	*ft_flstnew(t_fvec **v)
{
	t_flist			*new;

	NULL_CHECK(!(new = (t_flist *)malloc(sizeof(t_flist))));
	if (v == NULL)
		new->v = NULL;
	else
		new->v = v;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}

void		ft_flstadd_tail(t_flist **alst, t_flist *new)
{
	t_flist		*head;
	t_flist		*tmp;

	tmp = *alst;
	head = tmp;
	if (!tmp)
	{
		*alst = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	*alst = head;
}
