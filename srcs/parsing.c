/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 18:51:51 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/21 13:39:07 by acarlson         ###   ########.fr       */
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

t_fvec			**char_tab_to_fvec_tab(char *str, size_t row)
{
	t_fvec		**new;
	size_t		col;
	int			color;
	double		z;

	col = 0;
	NULL_CHECK(!(new = (t_fvec **)malloc((\
						get_len(str) + 1) * sizeof(t_fvec *))));
	while (*str)
	{
		RET_IF(!(ISDIGIT(*str) || *str == '-'), NULL);
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
		new[col] = fvec_new(ft_vectnew((double)col, (double)row, (double)z), color);
		col++;
	}
	new[col] = NULL;
	return (new);
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
		fvec_tab = char_tab_to_fvec_tab(line, row);
		if (!fvec_tab)
		{
			printf("%s\n", line);
			return (2);
		}
		ft_flstadd_tail(&(info->vals), ft_flstnew(fvec_tab));
		free(line);
		row++;
	}
	RET_IF(n == -1, 1);
	info->windowwidth = 600;
	info->windowheight = 600;
	return (0);
}
