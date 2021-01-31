/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 15:10:25 by paminna           #+#    #+#             */
/*   Updated: 2021/01/31 18:14:59 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

int main(void)
{
	void *mlx;
	void *mlx_win;
	t_data img;
	char    *dst;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1200, 780, "Hey, cutie pie!");
	// img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
    //                              &img.endian);
	mlx_loop(mlx);
}