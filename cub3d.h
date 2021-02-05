/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:11:57 by paminna           #+#    #+#             */
/*   Updated: 2021/02/05 16:32:51 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include <mlx.h>
#include <stdio.h> //

typedef struct  		s_data
{
    void        		*img;
    char       			*addr;
    int         		bits_per_pixel;
    int         		line_length;
    int         		endian;
	unsigned int 		color;
	void 				*mlx;
	void 				*mlx_win;
	int					x;
	int					y;
	// char 				**map;
	// int 				i;
	// int 				j;
}               		t_data;

#endif