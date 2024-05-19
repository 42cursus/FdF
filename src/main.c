/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelov <abelov@student.42london.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 07:18:11 by abelov            #+#    #+#             */
/*   Updated: 2024/05/18 07:18:12 by abelov           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sysexits.h>
#include "ft_fdf.h"

int	main(int argc, char **argv)
{
	t_fdf_struct fdf;

	ft_printf("FdF Test Program\n");
	check_endianness();

	if (argc != 2) {
		ft_printf("Usage: %s <filename>\n",*argv);
		exit(EX_USAGE);
	}
	fdf.filename = argv[1];
	fdf.map = NULL;
	fdf.custom_colour_flag = 0;

	load_data(&fdf);
	return (EX_OK);
}
