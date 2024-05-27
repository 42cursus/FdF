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
# include "ft/gnl.h"
# include "ft/libft.h"
# include "mlx.h"
# include "fdf/util.h"

#define FT_OFF 60
#define FT_SPARE FT_OFF + FT_OFF

/**
 * What is the strict aliasing rule?
 * 	https://stackoverflow.com/questions/98650/
 *
 * How to use a union along with two structs + more:
 * 	https://stackoverflow.com/questions/28596446/
 *
 * See also:
 * 	Embedded C. Struct and Union, Bit Fields in A Nutshell
 * 		https://atadiat.com/en/e-embedded-c-struct-union-part-2/
 */
typedef struct s_content
{
	void	*data;
	int		size;
}		t_cont;



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
	t_xvar		*mlx;
	t_win_list	*main_win;
	t_map_row	*map;
	int			cols;
	int			rows;
	int			b_scale;
	int			z_scale;
	int			max_height;
	char		*filename;
	int			custom_colour_flag;
	int			endianness;
	t_img		*canvas;
} t_fdf;

void load_data(t_fdf *fdf);
void data_convert(t_fdf *fdf, t_map_row *row);
void on_expose(t_fdf *fdf);

#endif //FT_FDF_H
