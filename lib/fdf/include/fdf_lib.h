/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_lib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 04:11:45 by abelov            #+#    #+#             */
/*   Updated: 2024/05/25 04:11:45 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_LIB_H
#define FDF_LIB_H

# include "util.h"

typedef struct s_fdf_struct	t_fdf;
void draw_line_d(t_fdf *fdf, int x1, int y1, int x2, int y2, int color1, int color2);

#endif //FDF_LIB_H
