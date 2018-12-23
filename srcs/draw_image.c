/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 19:39:33 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/23 13:31:39 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		draw_line_color_gradient(t_fdf *info, t_fvec *v, t_fvec *w)	// TODO: implement
{
	draw_line_bresenham(info, v->v, w->v, v->color);
}

void		draw_image(t_fdf *info) // TODO: make this draw it properly.  Give it an angle
{
	t_flist		*ptr;
	size_t		col;

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
