# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/08 20:13:09 by dchernik          #+#    #+#              #
#    Updated: 2026/06/28 00:03:43 by dchernik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC=cc

# Executable name
NAME=cub3D

# If 0, the debugging is turned off
DEBUG_LVL=0

# Library paths
# The `libft` library has to be built
LIBFT_PATH=libft/
LIBFT_A=$(LIBFT_PATH)/libft.a

# The `vector` library has to be built
VECTOR_PATH=vector/
VECTOR_A=$(VECTOR_PATH)/libvector.a

MLX_DIR=mlx42/
MLX_BUILD_DIR=$(MLX_DIR)/build
MLX_A=$(MLX_BUILD_DIR)/libmlx42.a

SRC_PATH=src/
OBJ_PATH=obj/

PARSER_SRCS=parser.c parse_map.c parse_validation.c \
			parse_color.c parse_elements.c parser_utils.c

RENDER_SRCS=cube.c texture.c cube_time.c render.c render2.c \
			render_texture.c raycast.c raycast_setters.c \
			player.c player_collision.c player_input.c \
			player_movement.c error.c

MINIMAP_SRCS=minimap.c minimap_walls.c minimap_fov.c minimap_utils.c

GRAPHX_SRCS=graphx_utils.c graphx_window.c graphx_line.c graphx_line_thick.c \
			graphx_polygon.c graphx_polygon2.c graphx_circle.c

SRCS=main.c $(PARSER_SRCS) $(RENDER_SRCS) $(MINIMAP_SRCS) $(GRAPHX_SRCS)

# We use 'addprefix' here just to avoid unnecessary repetition of file names
OBJS=$(addprefix $(OBJ_PATH)/, $(SRCS:.c=.o))

# Let's define all header that can affect object files
# This avoids stale object files when a structure layout changes
PROJECT_HDRS=$(SRC_PATH)/cube.h \
			 $(SRC_PATH)/graphx.h \
			 $(SRC_PATH)/minimap.h \
			 $(SRC_PATH)/parser.h \
			 $(SRC_PATH)/player.h \
			 $(SRC_PATH)/render.h

LIB_HDRS=$(SRC_PATH)/libft.h \
		 $(SRC_PATH)/vector.h \
		 $(SRC_PATH)/MLX42.h

HDRS=$(PROJECT_HDRS) $(LIB_HDRS)


# C compiler options
CFLAGS:=-Wall -Werror -Wextra

ifeq ($(DEBUG_LVL),1)
CFLAGS+=-O0 -g3 -DDEBUG=1
MLX_DEBUG:=-DDEBUG=1
else
CFLAGS+=-O2 -DDEBUG=0
MLX_DEBUG:=-DDEBUG=0
endif

INCLUDES=-I$(LIBFT_PATH) \
		 -I$(VECTOR_PATH) \
		 -I$(MLX_DIR)/include \
		 -I$(MLX_DIR)/include/MLX42

LIBFLAGS=-ldl -lglfw -pthread -lm -lGL


all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A) $(VECTOR_A) $(MLX_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_A) $(VECTOR_A) $(MLX_A) \
	$(LIBFLAGS) -o $(NAME)

# Here we build libraries
$(LIBFT_A):
	$(MAKE) -C $(LIBFT_PATH) bonus

$(VECTOR_A):
	$(MAKE) -C $(VECTOR_PATH)

$(MLX_A):
	cmake -B $(MLX_BUILD_DIR) $(MLX_DEBUG) $(MLX_DIR)
	cmake --build $(MLX_BUILD_DIR) -j$(shell nproc --all)

# Yeah.. it's redundant to specify libft.h, vector.h and MLX42.h
# as dependencies for each source file. However, since these are
# considered our libraries, we may want to use functions from them
# at any moment, so why not keep them just in case

# Here we build all source files manually
$(OBJ_PATH)/main.o: $(SRC_PATH)/main.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/main.c -o $(OBJ_PATH)/main.o

# ================================== PARSER ==================================

$(OBJ_PATH)/parser.o: $(SRC_PATH)/parser.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/parser.c -o $(OBJ_PATH)/parser.o

$(OBJ_PATH)/parse_map.o: $(SRC_PATH)/parse_map.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/parse_map.c -o $(OBJ_PATH)/parse_map.o

$(OBJ_PATH)/parse_validation.o: $(SRC_PATH)/parse_validation.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/parse_validation.c -o $(OBJ_PATH)/parse_validation.o

$(OBJ_PATH)/parse_color.o: $(SRC_PATH)/parse_color.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/parse_color.c -o $(OBJ_PATH)/parse_color.o

$(OBJ_PATH)/parse_elements.o: $(SRC_PATH)/parse_elements.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/parse_elements.c -o $(OBJ_PATH)/parse_elements.o

$(OBJ_PATH)/parser_utils.o: $(SRC_PATH)/parser_utils.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/parser_utils.c -o $(OBJ_PATH)/parser_utils.o

# ================================== RENDER  ==================================

$(OBJ_PATH)/cube.o: $(SRC_PATH)/cube.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/cube.c -o $(OBJ_PATH)/cube.o

$(OBJ_PATH)/texture.o: $(SRC_PATH)/texture.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/texture.c -o $(OBJ_PATH)/texture.o

$(OBJ_PATH)/cube_time.o: $(SRC_PATH)/cube_time.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/cube_time.c -o $(OBJ_PATH)/cube_time.o

$(OBJ_PATH)/render.o: $(SRC_PATH)/render.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/render.c -o $(OBJ_PATH)/render.o

$(OBJ_PATH)/render2.o: $(SRC_PATH)/render2.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/render2.c -o $(OBJ_PATH)/render2.o

$(OBJ_PATH)/render_texture.o: $(SRC_PATH)/render_texture.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/render_texture.c -o $(OBJ_PATH)/render_texture.o

$(OBJ_PATH)/raycast.o: $(SRC_PATH)/raycast.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/raycast.c -o $(OBJ_PATH)/raycast.o

$(OBJ_PATH)/raycast_setters.o: $(SRC_PATH)/raycast_setters.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/raycast_setters.c -o $(OBJ_PATH)/raycast_setters.o

$(OBJ_PATH)/player.o: $(SRC_PATH)/player.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/player.c -o $(OBJ_PATH)/player.o

$(OBJ_PATH)/player_collision.o: $(SRC_PATH)/player_collision.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/player_collision.c -o $(OBJ_PATH)/player_collision.o

$(OBJ_PATH)/player_input.o: $(SRC_PATH)/player_input.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/player_input.c -o $(OBJ_PATH)/player_input.o

$(OBJ_PATH)/player_movement.o: $(SRC_PATH)/player_movement.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/player_movement.c -o $(OBJ_PATH)/player_movement.o

$(OBJ_PATH)/error.o: $(SRC_PATH)/error.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/error.c -o $(OBJ_PATH)/error.o


# ================================= MINIMAP  ==================================

$(OBJ_PATH)/minimap.o: $(SRC_PATH)/minimap.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/minimap.c -o $(OBJ_PATH)/minimap.o

$(OBJ_PATH)/minimap_walls.o: $(SRC_PATH)/minimap_walls.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/minimap_walls.c -o $(OBJ_PATH)/minimap_walls.o

$(OBJ_PATH)/minimap_fov.o: $(SRC_PATH)/minimap_fov.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/minimap_fov.c -o $(OBJ_PATH)/minimap_fov.o

$(OBJ_PATH)/minimap_utils.o: $(SRC_PATH)/minimap_utils.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/minimap_utils.c -o $(OBJ_PATH)/minimap_utils.o

# ================================== GRAPHX ===================================

$(OBJ_PATH)/graphx_utils.o: $(SRC_PATH)/graphx_utils.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/graphx_utils.c -o $(OBJ_PATH)/graphx_utils.o

$(OBJ_PATH)/graphx_window.o: $(SRC_PATH)/graphx_window.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/graphx_window.c -o $(OBJ_PATH)/graphx_window.o

$(OBJ_PATH)/graphx_line.o: $(SRC_PATH)/graphx_line.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/graphx_line.c -o $(OBJ_PATH)/graphx_line.o

$(OBJ_PATH)/graphx_line_thick.o: $(SRC_PATH)/graphx_line_thick.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/graphx_line_thick.c -o $(OBJ_PATH)/graphx_line_thick.o

$(OBJ_PATH)/graphx_polygon.o: $(SRC_PATH)/graphx_polygon.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/graphx_polygon.c -o $(OBJ_PATH)/graphx_polygon.o

$(OBJ_PATH)/graphx_polygon2.o: $(SRC_PATH)/graphx_polygon2.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/graphx_polygon2.c -o $(OBJ_PATH)/graphx_polygon2.o

$(OBJ_PATH)/graphx_circle.o: $(SRC_PATH)/graphx_circle.c $(HDRS)
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/graphx_circle.c -o $(OBJ_PATH)/graphx_circle.o


# Other rules we obliged to have
clean:
	rm -rf $(OBJS)
	$(MAKE) -C $(LIBFT_PATH) clean
	$(MAKE) -C $(VECTOR_PATH) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_PATH) fclean
	$(MAKE) -C $(VECTOR_PATH) fclean
	rm -rf $(MLX_BUILD_DIR)

re: fclean all

.PHONY: all clean fclean re
