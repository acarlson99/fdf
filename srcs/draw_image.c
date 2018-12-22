/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/21 19:39:33 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/21 22:12:55 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		draw_image(t_fdf *info)
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
				draw_line_bresenham(info, ptr->v[col]->v, ptr->v[col + 1]->v, WHITE);
			if (ptr->next)
				draw_line_bresenham(info, ptr->v[col]->v, ptr->next->v[col]->v, WHITE);
			col++;
		}
		ptr = ptr->next;
	}
}
