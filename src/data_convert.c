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
void	parse_word(t_fdf *fdf, t_map_row *row, int col);

void	data_convert(t_fdf *fdf, t_map_row *row)
{
	int		curr;
	int		row_size;

	row_size = (int)ft_get_tab_size((void **) row->word_tab);
	if (row_size != fdf->cols)
	{
		ft_printf("Found wrong line length. Exiting.\n");
		exit(cleanup(fdf) + 1);
	}
	allocate_arrays(fdf, row);
	curr = fdf->cols;
	while (curr--)
		row->colours[curr] = WHITE_COLOR;
	while (row->word_tab[++curr])
		parse_word(fdf, row, curr);
}

void	parse_word(t_fdf *fdf, t_map_row *row, int col)
{
	char	*endptr;

	row->heights[col] = (double)ft_strtol(row->word_tab[col], &endptr, 0);
	if (fdf->max_height < row->heights[col])
		fdf->max_height = row->heights[col];
	if (*endptr == ',')
	{
		row->colours[col] = (int)ft_strtoul(endptr + 1, NULL, 0);
		fdf->custom_colour_flag = 1;
	}
	free(row->word_tab[col]);
	row->word_tab[col] = NULL;
}

void	allocate_arrays(const t_fdf *fdf, t_map_row *row)
{
	double		*heights;
	int			*colours;

	heights = (double *)malloc(fdf->cols * sizeof(double));
	if (!heights)
		exit(cleanup(fdf) + 1);
	row->heights = heights;
	colours = (int *)malloc((fdf->cols) * sizeof(int));
	if (!colours)
		exit(cleanup(fdf) + 1);
	row->colours = colours;
}
