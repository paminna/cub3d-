cmake_minimum_required(VERSION 3.17)
project(Cub3D C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_subdirectory(./libft)

add_executable(Cub3D
		ft_moving.c
		ft_parse_utils.c
		ft_parse_utils_2.c
		ft_parser.c
		ft_raycast.c
		ft_raycast_walls.c
		ft_screenshoot.c
		ft_sprites.c
		ft_utils.c
		ft_validate.c
		get_next_line.c
		main.c
		)

if (APPLE)
	target_link_libraries(Cub3D
#			Cub3D ${CMAKE_SOURCE_DIR}/libft/libft.a
			libft
			"-framework OpenGL"
			"-framework AppKit"
			${CMAKE_SOURCE_DIR}/libmlx.a
			)
endif(APPLE)