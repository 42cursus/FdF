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
# include <fdf/fdf_lib.h>
# include "ft/gnl.h"
# include "ft/libft.h"
# include "mlx.h"
# include "fdf/util.h"

# define WHITE_COLOR 0xffffff

typedef struct s_map_row	t_map_row;
struct s_map_row {
	char		*line;
	char		**word_tab;
	double		*heights;
	int			*colours;
	t_map_row	*next;
};

typedef struct s_fdf_struct {
	struct s_fdf_win {
		int	width;
		int	height;
	}			win;
	t_point		offset;
	t_xvar		*mlx;
	t_win_list	*root;
	t_map_row	*map;
	int			cols;
	int			rows;
	double		xy_scale;
	double		z_scale;
	double		max_height;
	char		*filename;
	int			custom_colour_flag;
	int			endianness;
	double		draw_offset_y;
	double		draw_offset_x;
	double		zoom;
	t_img		*canvas;
}	t_fdf;

void	load_data(t_fdf *fdf);
void	data_convert(t_fdf *fdf, t_map_row *row);
void	on_expose(t_fdf *fdf);
int		key_win(int key, t_fdf *fdf);
int		mouse_win(int button, int x, int y, void *p);
int		exit_win(const t_fdf *fdf);
int		expose_win(t_fdf *fdf);
void	calculate_zoom(t_fdf *const fdf);
t_point	get_point(t_fdf *fdf, t_map_row *row, int col, int crow);
void	replace_image(t_fdf *fdf);
#endif //FT_FDF_H
