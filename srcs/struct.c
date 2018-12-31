/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 18:51:18 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/30 23:41:50 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static const int g_projection_arr[] =
{
	['p'] = PAR,
	['i'] = ISO,
};

t_fvec	*fvec_new(t_vect3 *v, int color)
{
	t_fvec		*new;

	new = (t_fvec *)malloc(sizeof(t_fvec));
	new->v = v;
	new->color = color;
	return (new);
}

t_fdf	*init_struct(void)
{
	t_fdf	*info;

	info = (t_fdf *)malloc(sizeof(t_fdf));
	info->mlx_ptr = NULL;
	info->win_ptr = NULL;
	info->windowwidth = 0;
	info->windowheight = 0;
	info->mod = 0;
	info->off_x = 0;
	info->off_y = 0;
	info->exec_name = NULL;
	info->filename = NULL;
	info->vals = NULL;
	info->vals_len = 0;
	info->rows = 0;
	info->p_type = 0;
	return (info);
}

int		options(t_fdf *info, int argc, char **argv)
{
	if (argc == 4)
		info->mod = ft_atoi(argv[3]);
	else
		info->mod = 15;
	return (0);
}

int		fill_struct(t_fdf *info, int argc, char **argv)
{
	int		n;

	info->exec_name = ft_strdup(argv[0]);
	if (argc < 2 || argc > 4)
		return (USG_ERR);
	if (argc >= 3)
	{
		if (ft_strlen(argv[2]) == 1 && ft_isin(argv[2][0], "pi"))
			info->p_type = g_projection_arr[TOLOWER(argv[2][0])];
		else
			return (USG_ERR);
	}
	RET_IF(options(info, argc, argv), USG_ERR);
	info->filename = ft_strdup(argv[1]);
	n = parse_file(info);
	RET_IF(n, n);
	info->off_x = (info->windowwidth / 3);
	info->off_y = (info->windowheight / 3);
	RET_IF(!(info->mlx_ptr = mlx_init()), MLX_ERR);
	RET_IF(!(info->win_ptr = mlx_new_window(info->mlx_ptr, info->windowwidth,\
			info->windowheight, ft_strrchr(info->exec_name, '/') + 1)), WIN_ERR);
	return (0);
}
