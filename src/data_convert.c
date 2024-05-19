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

void data_convert(t_fdf_struct *fdf, t_map_row *node)
{
	long *long_array;
	int *int_array;
	long height;
	unsigned long colour;
	char *endptr;
	int i;
	t_map_row *current_node;
	t_fdf_struct *l_fdf;

	current_node = node;
	l_fdf = fdf;
	long_array = (long *)malloc((long)fdf->cols << 3);
	current_node->heights = long_array;
	int_array = (int *)malloc((long)l_fdf->cols << 2);
	current_node->colours = int_array;
	i = l_fdf->cols;
	while (i != 0)
		current_node->colours[--i] = 0xffffff;
	i = 0;
	while( true ) {
		if (l_fdf->cols <= i)
			return;
		if (current_node->word_tab[i] == NULL) break;
		height = strtol(current_node->word_tab[i],&endptr,0);
		current_node->heights[i] = height;
		if ((long) l_fdf->max_height < current_node->heights[i])
			l_fdf->max_height = (int) current_node->heights[i];
		if (*endptr == ',') {
			colour = strtoul(endptr + 1,NULL,0);
			current_node->colours[i] = (int)colour;
			l_fdf->custom_colour_flag = 1;
		}
		i++;
	}
	ft_printf("Found wrong line length. Exiting.\n");
	/* WARNING: Subroutine does not return */
	exit(1);
}
