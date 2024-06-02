/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_convert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 06:06:02 by abelov            #+#    #+#             */
/*   Updated: 2024/05/19 06:06:02 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include <string.h>

void	allocate_arrays(const t_fdf *fdf, t_map_row *row);

void	data_convert(t_fdf *fdf, t_map_row *row)
{
	double	height;
	char	*endptr;
	int		curr;
	int		col;

	allocate_arrays(fdf, row);
	curr = fdf->cols;
	while (curr--)
		row->colours[curr] = WHITE_COLOR;
	while (row->word_tab[++curr])
	{
		height = (double) ft_strtol(row->word_tab[curr], &endptr, 0);
		row->heights[curr] = height;
		if (fdf->max_height < row->heights[curr])
			fdf->max_height = row->heights[curr];
		if (*endptr == ',')
		{
			col = (int)ft_strtoul(endptr + 1, NULL, 0);
			row->colours[curr] = (int)col;
			fdf->custom_colour_flag = 1;
		}
		free(row->word_tab[curr]);
	}
	if (curr < fdf->cols)
		exit(1);
}

void	allocate_arrays(const t_fdf *fdf, t_map_row *row)
{
	double		*heights;
	int			*colours;

	heights = (double *)malloc(fdf->cols * sizeof(double));
	if (!heights)
		exit_win(fdf);
	row->heights = heights;
	colours = (int *)malloc((fdf->cols) * sizeof(int));
	if (!colours)
		exit_win(fdf);
	row->colours = colours;
}
