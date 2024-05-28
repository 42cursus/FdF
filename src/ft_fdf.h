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
#include <fdf/fdf_lib.h>
# include "ft/gnl.h"
# include "ft/libft.h"
# include "mlx.h"
# include "fdf/util.h"

#define MULT1 7
#define MULT2 10
#define FT_OFF 180
# define NUM_5	 0x35 /* (53) Number 5 on the main keyboard */
# define EXIT_KEY NUM_5
#define UP 65362
#define DOWN 65364
#define RIGHT 65363
#define LEFT 65361

typedef struct s_map_row t_map_row;
struct s_map_row {
	char		*line;
	char		**word_tab;
	long		*heights;
	int			*colours;
	t_map_row 	*next;
};

typedef struct s_fdf_struct {
	struct s_fdf_win {
		int width;
		int height;
	}			win;
	t_point		offset;
	t_xvar		*mlx;
	t_win_list	*root;
	t_map_row	*map;
	int			cols;
	int			rows;
	int			xy_scale;
	int			z_scale;
	int			max_height;
	char		*filename;
	int			custom_colour_flag;
	int			endianness;
	long		draw_offset_y;
	int			draw_offset_x;
	t_img		*canvas;
} t_fdf;

void load_data(t_fdf *fdf);
void data_convert(t_fdf *fdf, t_map_row *row);
void on_expose(t_fdf *fdf);
int key_win(int key, t_fdf *fdf);

#endif //FT_FDF_H
