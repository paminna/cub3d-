/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/06 19:37:45 by paminna           #+#    #+#             */
/*   Updated: 2021/03/10 11:00:09 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// void ft_parser(t_data *img, t_ray *ray)
// {
// 	int fd;
// 	char *str;
// 	int i;
	
// 	i = 0;
// 	str = NULL;
// 	fd = open("map.cub", O_RDONLY);
// 	while (get_next_line(fd, &str) != 0 && str[0] != '0' && str[1] != '1')
// 	{
// 		if (str[0] == 'R' && str[1] == ' ')
// 			img->width = ft_find_numbers(&str[0]);
// 		if (str[0] == 'N' && str[1] == 'O')
// 			img->no = ft_find_color(&str[0]);
// 		if (str[0] == 'S' && str[1] == 'O')
// 			img->so = ft_find_color(&str[0]);
// 		if (str[0] == 'W' && str[1] == 'E')
// 			img->we = ft_find_color(&str[0]);
// 		if (str[0] == 'E' && str[1] == 'A')
// 			img->ea = ft_find_color(&str[0]);
// 		if (str[0] == 'C' && str[1] == ' ')
// 			img->c = ft_find_color(&str[0]);
// 		if (str[0] == 'F' && str[1] == ' ')
// 			img->f = ft_find_color(&str[0]);
// 	}
// 	while (get_next_line(fd, &str) != 0)
// 	{
// 		while ((str[i] != '0' || str[i] != '1'))
// 			i++;
// 		while (str[i] != '\0')
// 		{
// 			while (str[i] == '1' || str[i] == '0')
// 				img->map[img->mapX++][img->mapY] = str[i];
// 			img->mapX = 0;
// 			img->mapY++;
// 			if (str[i] == 'N')
// 			{
// 				ray->planeX = 0;
// 				ray->planeY = 0.66;
// 				ray->dirX = -1;
// 				ray->dirY = 0;
// 				img->map[img->mapX++][img->mapY] = '0';
// 			}
// 			if (str[i] == 'S')
// 			{
// 				ray->planeX = 0;
// 				ray->planeY = -0.66;
// 				ray->dirX = 1;
// 				ray->dirY = 0;
// 				img->map[img->mapX++][img->mapY] = '0';
// 			}
// 			if (str[i] == 'E')
// 			{
// 				ray->planeX = 1;
// 				ray->planeY = 0;
// 				ray->dirX = 0;
// 				ray->dirY = 0.66;
// 				img->map[img->mapX++][img->mapY] = '0';
// 			}
// 			if (str[i] == 'W')
// 			{	
// 				ray->planeX = -1;
// 				ray->planeY = 0;
// 				ray->dirX = 0;
// 				ray->dirY = -0.66;
// 				img->map[img->mapX++][img->mapY] = '0';
// 			}
// 		}
// 	}
// }

// int main()
// {
// 	char map[8][8] =
// 	{	
//  	{'1', '1', '1', '1', '1', '1', '1', '1'},
//  	{'1', '0', '1', '0', '0', '0', '0', '1'},
//  	{'1', '0', '1', '0', '0', '0', '0', '1'},
//  	{'1', '0', '0', '0', '0', '1', '1', '1'},
//  	{'1', '0', 'p', '0', '0', '0', '0', '1'},
// 	{'1',0001111},
// 	{'1', '0', 'p', '0', '0', '0', '0', '1'},
// 	{'1', '0', 'p', '0', '0', '0', '0', '1'}
// 	};
// }