/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 23:50:09 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/30 23:51:43 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void		iso(double *x, double *y, int z, t_fdf *info)
{
	int		prev_x;
	int		prev_y;

	prev_x = *x;
	prev_y = *y;
	*x = info->off_x + (prev_x - prev_y) * cos(0.523599);
	*y = info->off_y + -z + (prev_x + prev_y) * sin(0.523599);
}

void			convert_iso(t_vect3 *v, t_fdf *info)
{
	iso(&v->x, &v->y, v->z, info);
}

int		ft_other_atoibase(const char *str, int base)
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
