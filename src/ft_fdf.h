/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fdf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 07:37:23 by abelov            #+#    #+#             */
/*   Updated: 2024/05/18 07:37:24 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_FDF_H
# define FT_FDF_H
# include <stdlib.h>
# include <stdbool.h>
# include <stdio.h>
# include "ft/get_next_line.h"
# include "ft/libft.h"
# include "mlx.h"
# include "fdf/util.h"

typedef struct s_map_row t_map_row;
struct s_map_row {
	char	*line;
	char	**word_tab;
	long	*heights;
	int		*colours;
	t_map_row * next;
};

typedef struct s_fdf_struct {
	int w_width;
	int w_height;
	t_xvar *mlx_app;
	t_win_list *main_win;
	t_map_row *map;
	int cols;
	int rows;
	int case_zoom;
	int z_size;
	int max_height;
	char *filename;
	int custom_colour_flag;
} t_fdf_struct;


void load_data(t_fdf_struct *fdf);
void data_convert(t_fdf_struct *fdf, t_map_row *node);

#endif //FT_FDF_H
