/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/19 15:01:26 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/21 22:06:47 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		h_line_draw(t_fdf *info, t_vect3 *v, t_vect3 *w, int color)
{
	double	d_err;
	double	err;
	int		y;
	int		x;

	d_err = fabs((w->y - v->y) / (w->x - v->x));
	err = 0.0;
	y = v->y;
	x = v->x;
	while (x <= w->x)
	{
		mlx_pixel_put(info->mlx_ptr, info->win_ptr, x, y, color);
		err += d_err;
		if (err >= 0.5)
		{
			y = y + ((w->y - v->y) < 0 ? -1 : 1) * 1;
			err -= 1.0;
		}
		x++;
	}
}

static void		v_line_draw(t_fdf *info, t_vect3 *v, t_vect3 *w, int color)
{
	double	d_err;
	double	err;
	int		y;
	int		x;

	d_err = fabs((w->x - v->x) / (w->y - v->y));
	err = 0.0;
	y = v->y;
	x = v->x;
	while (y <= w->y)
	{
		mlx_pixel_put(info->mlx_ptr, info->win_ptr, x, y, color);
		err += d_err;
		if (err >= 0.5)
		{
			x = x + ((w->x - v->x) < 0 ? -1 : 1) * 1;
			err -= 1.0;
		}
		y++;
	}
}

void			draw_line_bresenham(t_fdf *info, t_vect3 *v, t_vect3 *w,\
									int color)
{
	double	d_x;
	double	d_y;

	RET_NONE(!info || !info->mlx_ptr || !info->win_ptr || !v || !w);
	d_x = w->x - v->x;
	d_y = w->y - v->y;
	if (v->x < w->x && d_x >= d_y)
		h_line_draw(info, v, w, color);
	else if (v->y < w->y && d_y >= d_x)
		v_line_draw(info, v, w, color);
	else if (v->y == w->y && v->x == w->x)
		mlx_pixel_put(info->mlx_ptr, info->win_ptr, v->x, v->y, color);
	else
		draw_line_bresenham(info, w, v, color);
}
