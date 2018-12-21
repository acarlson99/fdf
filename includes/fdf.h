/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 18:34:13 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/21 13:00:30 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"

#include <stdio.h>	// TODO: sweet god delete this

# define PAR 0
# define ISO 1
# define CON 2

# define USG_ERR 1
# define FILE_ERR 2

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

# define COLOR(x, y, w, h) ((x * 255) / w + ((((w - x) * 255) / w) << 16) + (((y * 255) / h) << 8))

typedef struct s_fvec
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
	char			*exec_name;
	char			*filename;
	t_flist			*vals;
	unsigned char	p_type;
}				t_fdf;

t_fdf	*init_struct(void);
int		fill_struct(t_fdf *info, int argc, char **argv);
int		parse_file(t_fdf *info);

void	draw_line_bresenham(t_fdf *info, t_vect3 *v, t_vect3 *w, int color);

void	ohfuck(t_fdf *info, int code);
t_fvec	*fvec_new(t_vect3 *v, int color);

t_flist	*ft_flstnew(t_fvec **v);
void		ft_flstadd_tail(t_flist **alst, t_flist *new);

#endif
