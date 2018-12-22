/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 18:51:51 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/21 22:15:12 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		ft_other_atoibase(const char *str, int base)
{
	int	n;
	int	sign;

	n = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str)
	{
		if (*str >= '0' && *str <= (MIN('0' + base - 1, '9')))
			n = n * base + *str - '0';
		else if (*str >= 'A' && *str <= ('A' + base - 11))
			n = n * base + *str - 'A' + 10;
		else
			break ;
		str++;
	}
	return (n * sign);
}

size_t			get_len(char *str)
{
	size_t		len;

	len = 0;
	while (*str)
	{
		while (ISWHITE(*str))
			str++;
		if (*str)
			len++;
		while (*str && !ISWHITE(*str))
			str++;
	}
	return (len);
}

#define DC (double)col
#define DR (double)row
#define DZ (double)z

int				char_tab_to_fvec_tab(t_fvec **new, char *str, size_t row)	// TODO: This still leaks on error
{
	size_t		col;
	int			color;
	double		z;

	RET_IF(!new, 1);
	col = 0;
	while (*str)
	{
		RET_IF(!(ISDIGIT(*str) || *str == '-'), 1);
		color = 0xFFFFFF;
		z = ft_atoi(str);
		while (ISDIGIT(*str) || *str == '-')
			str++;
		if (*str == ',')
		{
			RET_IF(*(str + 1) != '0' || *(str + 2) != 'x', PARS_ERR);
			ELSE_DO(str += 3);
			color = ft_other_atoibase(str, 16) - 0xA;
			WHILE_DO(ISDIGIT(*str) || (*str >= 'A' && *str <= 'F'), str++);
		}
		DO_IF(*str == ' ', str++);
		new[col] = fvec_new(ft_vectnew(DC, DR, DZ), color);
		col++;
	}
	new[col] = NULL;
	return (0);
}

int				free_line(char **line, int code)
{
	free(*line);
	return (code);
}

int				parse_file(t_fdf *info)
{
	t_fvec	**fvec_tab;
	char	*line;
	size_t	row;
	int		n;
	int		fd;

	fd = open(info->filename, O_RDONLY);
	row = 0;
	while ((n = get_next_line(fd, &line)) > 0)
	{
		RET_IF(row != 0 && get_len(line) != info->vals_len,\
				free_line(&line, PARS_ERR));
		info->vals_len = row == 0 ? get_len(line) : info->vals_len;
		RET_IF(!(fvec_tab = (t_fvec **)malloc((info->vals_len + 1)\
										* sizeof(t_fvec *))), PARS_ERR);
		RET_IF(char_tab_to_fvec_tab(fvec_tab, line, row), PARS_ERR);
		ft_flstadd_tail(&(info->vals), ft_flstnew(fvec_tab));
		free(line);
		row++;
	}
	RET_IF(n == -1, FILE_ERR);
	info->windowwidth = 600;
	info->windowheight = 600;
	return (0);
}
