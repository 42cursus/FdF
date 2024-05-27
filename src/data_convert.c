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
	long			*long_array;
	int				*int_array;
	long			height;
	char			*endptr;
	int				curr_col;

	long_array = (long *)malloc(fdf->cols * sizeof(long));
	row->heights = long_array;
	int_array = (int *)malloc(fdf->cols * sizeof(int));
	row->colours = int_array;
	curr_col = fdf->cols;
	while (curr_col--)
		row->colours[curr_col] = 0xffffff;
	while(row->word_tab[++curr_col])
	{
		height = ft_strtol(row->word_tab[curr_col], &endptr, 0);
		row->heights[curr_col] = height;
		if ((long) fdf->max_height < row->heights[curr_col])
			fdf->max_height = (int) row->heights[curr_col];
		if (*endptr == ',')
		{
			row->colours[curr_col] = (int)ft_strtoul(endptr + 1,
													 NULL, 0);
			fdf->custom_colour_flag = 1;
		}
	}
	if (curr_col < fdf->cols)
	{
		ft_printf("Found wrong line length. Exiting.\n");
		exit(1);
	}
}
