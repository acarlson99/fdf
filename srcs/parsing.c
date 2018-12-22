/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 18:51:51 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/21 19:36:29 by acarlson         ###   ########.fr       */
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
			if (*(str + 1) == '0' && *(str + 2) == 'x')
				str += 3;
			color = ft_other_atoibase(str, 16);
			while (ISDIGIT(*str) || (*str >= 'A' && *str <= 'F'))
				str++;
		}
		if (*str == ' ')
			str++;
		new[col] = fvec_new(ft_vectnew(DC, DR, DZ), color);
		col++;
	}
	new[col] = NULL;
	return (0);
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
		RET_IF(row != 0 && get_len(line) != info->vals_len, PARS_ERR);
		if (row == 0)
			info->vals_len = get_len(line);
		RET_IF(!(fvec_tab = (t_fvec **)malloc((info->vals_len + 1)\
										* sizeof(t_fvec *))), PARS_ERR);
		char_tab_to_fvec_tab(fvec_tab, line, row);
		ft_flstadd_tail(&(info->vals), ft_flstnew(fvec_tab));
		free(line);
		row++;
	}
	RET_IF(n == -1, FILE_ERR);
	info->windowwidth = 600;
	info->windowheight = 600;
	return (0);
}
