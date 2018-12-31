/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 18:51:51 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/31 15:39:30 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#define ISVAL(c) (ISDIGIT(c) || (TOLOWER(c) >= 'a' && TOLOWER(c) <= 'f'))

#define DC (double)col
#define DR (double)row
#define DZ (double)z

int				char_tab_to_fvec_tab(t_fvec **new, char *str, size_t row,
										double mod)
{
	size_t		col;
	int			color;
	double		z;

	RET_IF(!new || !str, 1);
	col = 0;
	while (*str)
	{
		WHILE_DO(*str == ' ', str++);
		RET_IF(*str && !(ISDIGIT(*str) || *str == '-'), 1);
		color = 0xFFFFFF;
		z = ft_atoi(str);
		WHILE_DO(ISDIGIT(*str) || *str == '-', str++);
		if (*str == ',')
		{
			RET_IF(*(str + 1) != '0' || *(str + 2) != 'x', PARS_ERR);
			ELSE_DO(str += 3);
			color = ft_other_atoibase(str, 16) - 0xA;
			WHILE_DO(ISVAL(*str), str++);
		}
		new[col] = fvec_new(ft_vectnew(DC * mod, DR * mod, DZ * mod), color);
		col++;
	}
	new[col] = NULL;
	return (0);
}

static int		free_line(char **line, int code)
{
	free(*line);
	return (code);
}

int				parse_file(t_fdf *info)
{
	t_fvec	**fvec_tab;
	char	*line;
	int		n;
	int		fd;

	fd = open(info->filename, O_RDONLY);
	while ((n = get_next_line(fd, &line)) > 0)
	{
		RET_IF(info->rows != 0 && get_len(line) != info->vals_len,\
				free_line(&line, PARS_ERR));
		info->vals_len = info->rows == 0 ? get_len(line) : info->vals_len;
		RET_IF(!(fvec_tab = (t_fvec **)malloc((info->vals_len + 1)\
										* sizeof(t_fvec *))), PARS_ERR);
		RET_IF(char_tab_to_fvec_tab(fvec_tab, line, info->rows,\
									info->mod), PARS_ERR);
		ft_flstadd_tail(&(info->vals), ft_flstnew(fvec_tab));
		free(line);
		info->rows++;
	}
	RET_IF(n == -1, FILE_ERR);
	info->windowwidth = 900;
	info->windowheight = 800;
	return (0);
}
