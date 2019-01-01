/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 19:39:33 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/31 16:09:19 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define ISO_RED(n) ((n & 0xFF0000) >> 4)
#define ISO_GRN(n) ((n & 0x00FF00) >> 2)
#define ISO_BLU(n) (n & 0x0000FF)

void		draw_line_color_gradient(t_fdf *info, t_fvec *v, t_fvec *w)
{
	draw_line_bresenham(info, v->v, w->v,								\
						(((ISO_RED(v->color) + ISO_RED(w->color)) / 2) << 4) \
						+ (((ISO_GRN(v->color) + ISO_GRN(w->color)) / 2) << 2) \
						+ (((ISO_BLU(v->color) + ISO_BLU(w->color)) / 2)));
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
