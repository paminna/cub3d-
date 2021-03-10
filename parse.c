/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paminna <paminna@stud.21-school.ru>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 18:02:01 by paminna           #+#    #+#             */
/*   Updated: 2021/03/08 18:19:22 by paminna          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void parse_resolution(int *height, int *width, char **line)
// {
// 	int i;
	
// 	i  = 0;
// 	while (*line[i] == ' ')
// 		i++;
// 	while (ft_isalpha(*line[i]) != 0)
// 	{
// 		*width = ft_atoi((const char *)line);
// 		i++;
// 	}
// 	while (*line[i] == ' ')
// 		i++;
// 	while (ft_isalpha(*line[i]) != 0)
// 	{
// 		*height = ft_atoi((const char *)line);
// 		i++;
// 	}
// }

// int main()
// {
// 	char *line;
// 	int fd;
// 	int width;
// 	int height;

// 	width = 0;
// 	height = 0;
// 	fd = open("map.cub", O_RDONLY);
// 	line = NULL;
// 	while (get_next_line(fd, &line) != 0)
// 	{
// 		if (line[0] == 'R' && line[1] == ' ')
// 			parse_resolution(&height, &width, &line);
// 		// if (line[0] == 'N' && line[1] == 'O')

// 		// if (line[0] == 'S' && line[1] == 'O')

// 		// if (line[0] == 'W' && line[1] == 'E')

// 		// if (line[0] == 'E' && line[1] == 'A')
		
// 		// if (line[0] == 'C' && line[1] == ' ')

// 		// if (line[0] == 'F' && line[1] == ' ')

// 	}
// }