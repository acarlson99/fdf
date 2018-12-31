/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/15 14:10:38 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/31 00:39:47 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ohfuck(t_fdf *info, int code)
{
	if (code == 1)
	{
		if (info)
			ft_printf("usage: %s <file> [{bold}p{nc}arallel {bold}i{nc}so] \
[modify_projection_size]\n", info->exec_name);
	}
	else if (code == 2)
		ft_printf("file read error\n");
	else if (code == 3)
		ft_printf("file parsing error\n");
	else if (code == 4)
		ft_printf("unable to create window\n");
	else if (code == 5)
		ft_printf("unable to create window\n");
	exit(1);
}

int		deal_key(int key, void *param)
{
	(void)param;
	if (key == 53 || key == 12)
		exit(0);
	return (0);
}

int		main(int argc, char **argv)
{
	t_fdf	*info;
	int		code;

	info = init_struct();
	code = fill_struct(info, argc, argv);
	if (code)
		ohfuck(info, code);
	if (!info->mlx_ptr)
		ohfuck(info, 3);
	else if (!info->win_ptr)
		ohfuck(info, 4);
	draw_image(info);
	mlx_key_hook(info->win_ptr, deal_key, (void *)0);
	mlx_loop(info->mlx_ptr);
}
