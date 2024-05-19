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

void load_data(t_fdf_struct *fdf)
{
	int fd;
	char *line;
	t_map_row *current_node;
	char **w_tab;
	bool is_last;
	t_map_row *next_node;

	fd = open(fdf->filename,0);
	if (fd != -1) {
		while (line = get_next_line(fd), line != NULL) {
			current_node = (t_map_row *)malloc(0x28);
			current_node->line = line;
			w_tab = ft_split(current_node->line, ' ');
			current_node->word_tab = w_tab;
			current_node->next = fdf->map;
			fdf->map = current_node;
		}
		close(fd);
		next_node = NULL;
		while (fdf->map != NULL) {
			current_node = fdf->map->next;
			fdf->map->next = next_node;
			next_node = fdf->map;
			fdf->map = current_node;
		}
		fdf->map = next_node;
		fdf->cols = 0;
		while( true ) {
			is_last = false;
			if (fdf->map != NULL) {
				is_last = fdf->map->word_tab[fdf->cols] != NULL;
			}
			if (!is_last) break;
			fdf->cols = fdf->cols + 1;
		}
		fdf->rows = 0;
		fdf->max_height = 0;
		next_node = fdf->map;
		while (next_node != NULL) {
			data_convert(fdf,next_node);
			fdf->rows = fdf->rows + 1;
			next_node = next_node->next;
		}
		return;
	}
	ft_printf("No file %s\n",fdf->filename);
	exit(1);
}
