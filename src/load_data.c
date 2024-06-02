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

void	read_lines_from_file(t_fdf *fdf);

void	load_data(t_fdf *fdf)
{
	t_map_row	*next;
	t_map_row	*row;

	read_lines_from_file(fdf);
	row = NULL;
	while (fdf->map != NULL)
	{
		next = fdf->map->next;
		fdf->map->next = row;
		row = fdf->map;
		fdf->map = next;
	}
	fdf->map = row;
	fdf->cols = (int)ft_get_tab_size((void **) fdf->map->word_tab);
	fdf->rows = 0;
	fdf->max_height = 0;
	row = fdf->map;
	while (row != NULL)
	{
		data_convert(fdf, row);
		(fdf->rows)++;
		row = row->next;
	}
}

void	read_lines_from_file(t_fdf *fdf)
{
	int			fd;
	char		*line;
	t_map_row	*row;
	char		**w_tab;

	fd = open(fdf->filename, 0);
	if (fd == -1)
	{
		ft_printf("Cannot open file %s\n", fdf->filename);
		exit(1);
	}
	line = get_next_line(fd);
	while (line)
	{
		row = (t_map_row *) malloc(sizeof(t_map_row));
		row->line = line;
		w_tab = ft_split(row->line, ' ');
		row->word_tab = w_tab;
		row->next = fdf->map;
		fdf->map = row;
		free(line);
		row->line = NULL;
		line = get_next_line(fd);
	}
	close(fd);
}
