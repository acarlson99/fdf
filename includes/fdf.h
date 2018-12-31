/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 18:34:13 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/30 23:16:21 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"

# define PAR 0
# define ISO 1
# define CON 2

# define USG_ERR 1
# define FILE_ERR 2
# define PARS_ERR 3
# define MLX_ERR 4
# define WIN_ERR 5

# define WHITE 0xFFFFFF
# define BLUE  0x0000FF
# define RED   0xFF0000
# define GREEN 0x00FF00
# define C1    0xFFFF00
# define C2    0xFF00FF
# define C3    0x00FFFF

/*
** x = x position
** y = y position
** w = windowwidth
** h = windowheight
*/

# define R(x, y, w, h) (((w - x) * 255) / w)
# define G(x, y, w, h) ((y * 255) / h)
# define B(x, y, w, h) ((x * 255) / w)
# define RGB(x,y,w,h) ((R(x,y,w,h) << 16) + (G(x,y,w,h) << 8) + B(x,y,w,h))

typedef struct	s_fvec
{
	t_vect3		*v;
	int			color;
}				t_fvec;

typedef struct	s_flist
{
	t_fvec				**v;
	struct s_flist		*prev;
	struct s_flist		*next;
}				t_flist;

typedef struct	s_fdf
{
	void			*mlx_ptr;
	void			*win_ptr;
	size_t			windowwidth;
	size_t			windowheight;
	double			mod;
	double			off_x;
	double			off_y;
	char			*exec_name;
	char			*filename;
	t_flist			*vals;
	size_t			vals_len;
	size_t			rows;
	unsigned char	p_type;
}				t_fdf;

t_fdf			*init_struct(void);
int				fill_struct(t_fdf *info, int argc, char **argv);
int				parse_file(t_fdf *info);

void			draw_line_bresenham(t_fdf *info, t_vect3 *v, t_vect3 *w,\
									int color);

void			ohfuck(t_fdf *info, int code);
t_fvec			*fvec_new(t_vect3 *v, int color);

t_flist			*ft_flstnew(t_fvec **v);
void			ft_flstadd_tail(t_flist **alst, t_flist *new);

void			draw_image(t_fdf *info);

void			convert_iso(t_vect3 *v, t_fdf *info);

#endif
