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

void data_convert(t_fdf *fdf, t_map_row *row)
{
	double	height;
	char	*endptr;
	int		curr;
	int		col;

	row->heights = (double *)malloc(fdf->cols * sizeof(double));
	row->colours = (int *)malloc((fdf->cols) * sizeof(int));

	curr = fdf->cols;
	while (curr--)
		row->colours[curr] = 0xffffff;
	while(row->word_tab[++curr])
	{
		height = (double)ft_strtol(row->word_tab[curr], &endptr, 0);
		row->heights[curr] = height;
		if (fdf->max_height < row->heights[curr])
			fdf->max_height = row->heights[curr];
		if (*endptr == ',')
		{
			col = (int)ft_strtoul(endptr + 1, NULL, 0);
			row->colours[curr] = (int)col;
			fdf->custom_colour_flag = 1;
		}
	}
	if (curr < fdf->cols)
	{
		ft_printf("Found wrong line length. Exiting.\n");
		exit(1);
	}
}
