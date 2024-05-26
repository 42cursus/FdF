/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 06:04:37 by abelov            #+#    #+#             */
/*   Updated: 2024/05/19 06:04:38 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"

void read_lines_from_file(t_fdf *fdf);

void load_data(t_fdf *fdf)
{
	t_map_row *current_node;
	bool has_next;
	t_map_row *row;

	read_lines_from_file(fdf);
	row = NULL;
	while (fdf->map != NULL) {
		current_node = fdf->map->next;
		fdf->map->next = row;
		row = fdf->map;
		fdf->map = current_node;
	}
	fdf->map = row;
	fdf->cols = 0;
	while (true)
	{
		has_next = false;
		if (fdf->map != NULL)
			has_next = fdf->map->word_tab[fdf->cols] != NULL;
		if (has_next)
			fdf->cols = fdf->cols + 1;
		else break ;
	}
	fdf->rows = 0;
	fdf->max_height = 0;
	row = fdf->map;
	while (row != NULL) {
		data_convert(fdf, row);
		fdf->rows = fdf->rows + 1;
		row = row->next;
	}
}

void read_lines_from_file(t_fdf *fdf)
{
	int			fd;
	char		*line;
	t_map_row	*row;
	char		**w_tab;

	fd = open(fdf->filename, 0);
	if (fd == -1)
	{
		ft_printf("No file %s\n", fdf->filename);
		exit(1);
	}
	while (line = get_next_line(fd), line != NULL)
	{
		row = (t_map_row *) malloc(sizeof(t_map_row));
		row->line = line;
		w_tab = ft_split(row->line, ' ');
		row->word_tab = w_tab;
		row->next = fdf->map;
		fdf->map = row;
	}
	close(fd);
}
