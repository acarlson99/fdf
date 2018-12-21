/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarlson <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 18:51:51 by acarlson          #+#    #+#             */
/*   Updated: 2018/12/20 22:47:05 by acarlson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

	col = 0;
	ft_printf("Len of %d: %zu\n", row, get_len(str));
	new = (t_fvec **)malloc((get_len(str) + 1) * sizeof(t_fvec *));
	while (*str)
	{
		str++;
	}
	(void)str;
	return (NULL);
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
		ft_printf("%s\n", line);
		free(line);
	}
	RET_IF(n == -1, 1);
	info->windowwidth = 600;
	info->windowheight = 600;
	return (0);
}
