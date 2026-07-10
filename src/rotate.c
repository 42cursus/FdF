/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 07:22:30 by abelov            #+#    #+#             */
/*   Updated: 2024/06/02 07:22:31 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fdf.h"
#include <math.h>

void	rotate_x(t_dpoint *point, double angle);
void	rotate_z(t_dpoint *point, double angle);
void	rotate_y(t_dpoint *point, double angle);

void	rotate_x(t_dpoint *point, double angle)
{
	double	y;
	double	z;

	y = point->y;
	z = point->z;
	point->y = y * cos(angle) - z * sin(angle);
	point->z = y * sin(angle) + z * cos(angle);
}

void	rotate_z(t_dpoint *point, double angle)
{
	double	x;
	double	y;

	x = point->x;
	y = point->y;
	point->x = x * cos(angle) - y * sin(angle);
	point->y = x * sin(angle) + y * cos(angle);
}

void	rotate_y(t_dpoint *point, double angle)
{
	double	x;
	double	z;

	x = point->x;
	z = point->z;
	point->x = x * cos(angle) + z * sin(angle);
	point->z = -x * sin(angle) + z * cos(angle);
}
