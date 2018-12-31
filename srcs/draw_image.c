/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 19:39:33 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/31 00:48:07 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		draw_line_color_gradient(t_fdf *info, t_fvec *v, t_fvec *w)
{
	draw_line_bresenham(info, v->v, w->v, (v->color + w->color) / 2);
}

void		conv(t_fdf *info)
{
	t_flist	*ptr;
	size_t	col;

	ptr = info->vals;
	while (ptr)
	{
		col = 0;
		while (ptr->v[col])
		{
			convert_iso(ptr->v[col]->v, info);
			col++;
		}
		ptr = ptr->next;
	}
}

void		draw_image(t_fdf *info)
{
	t_flist		*ptr;
	size_t		col;

	if (info->p_type == ISO)
		conv(info);
	ptr = info->vals;
	while (ptr)
	{
		col = 0;
		while (ptr->v[col])
		{
			if (ptr->v[col] && ptr->v[col + 1])
				draw_line_color_gradient(info, ptr->v[col], ptr->v[col + 1]);
			if (ptr->next)
				draw_line_color_gradient(info, ptr->v[col], ptr->next->v[col]);
			col++;
		}
		ptr = ptr->next;
	}
}
