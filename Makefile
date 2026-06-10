# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dchernik <dchernik@student.42urduliz.com>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/08 20:13:09 by dchernik          #+#    #+#              #
#    Updated: 2026/06/10 15:13:33 by dchernik         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC=cc

# Executable name
NAME=cub3D

# If 0, the debugging is turned off
DEBUG_LVL=1

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

RENDER_SRCS=cube.c player.c player2.c error.c

MINIMAP_SRCS=minimap.c minimap_walls.c minimap_utils.c

GRAPHX_SRCS=graphx_line.c graphx_line_thick.c \
			graphx_polygon.c graphx_polygon2.c \
			graphx_circle.c graphx_utils.c

SRCS=main.c $(PARSER_SRCS) $(RENDER_SRCS) $(MINIMAP_SRCS) $(GRAPHX_SRCS)

# We use 'addprefix' here just to avoid unnecessary repetition of file names
OBJS=$(addprefix $(OBJ_PATH)/, $(SRCS:.c=.o))

# C compiler options
CFLAGS=-Wall -Werror -Wextra -O0 -g3

ifeq ($(DEBUG_LVL),1)
CFLAGS=-Wall -Wextra -Werror -O0 -g3 -DDEBUG=1
MLX_DEBUG=-DDEBUG=1
else
CFLAGS=-Wall -Wextra -Werror -DDEBUG=0
MLX_DEBUG=-DDEBUG=0
endif

INCLUDES=-I$(LIBFT_PATH) -I$(VECTOR_PATH) -I$(MLX_DIR)/include
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
$(OBJ_PATH)/main.o: $(SRC_PATH)/main.c $(SRC_PATH)/cube.h \
	$(SRC_PATH)/parser.h \
	$(LIBFT_PATH)/libft.h $(VECTOR_PATH)/vector.h \
	$(MLX_DIR)/include/MLX42/MLX42.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_PATH)/main.c -o $(OBJ_PATH)/main.o

# ================================== PARSER ==================================

$(OBJ_PATH)/parser.o: $(SRC_PATH)/parser.c $(SRC_PATH)/parser.h \
	$(LIBFT_PATH)/libft.h $(VECTOR_PATH)/vector.h \
	$(MLX_DIR)/include/MLX42/MLX42.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/parser.c -o $(OBJ_PATH)/parser.o

$(OBJ_PATH)/parse_map.o: $(SRC_PATH)/parse_map.c $(SRC_PATH)/parser.h \
	$(LIBFT_PATH)/libft.h $(VECTOR_PATH)/vector.h \
	$(MLX_DIR)/include/MLX42/MLX42.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/parse_map.c -o $(OBJ_PATH)/parse_map.o

$(OBJ_PATH)/parse_validation.o: $(SRC_PATH)/parse_validation.c $(SRC_PATH)/parser.h \
	$(LIBFT_PATH)/libft.h $(VECTOR_PATH)/vector.h \
	$(MLX_DIR)/include/MLX42/MLX42.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/parse_validation.c -o $(OBJ_PATH)/parse_validation.o

$(OBJ_PATH)/parse_color.o: $(SRC_PATH)/parse_color.c $(SRC_PATH)/parser.h \
	$(LIBFT_PATH)/libft.h $(VECTOR_PATH)/vector.h \
	$(MLX_DIR)/include/MLX42/MLX42.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/parse_color.c -o $(OBJ_PATH)/parse_color.o

$(OBJ_PATH)/parse_elements.o: $(SRC_PATH)/parse_elements.c $(SRC_PATH)/parser.h \
	$(LIBFT_PATH)/libft.h $(VECTOR_PATH)/vector.h \
	$(MLX_DIR)/include/MLX42/MLX42.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/parse_elements.c -o $(OBJ_PATH)/parse_elements.o

$(OBJ_PATH)/parser_utils.o: $(SRC_PATH)/parser_utils.c $(SRC_PATH)/parser.h \
	$(LIBFT_PATH)/libft.h $(VECTOR_PATH)/vector.h \
	$(MLX_DIR)/include/MLX42/MLX42.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/parser_utils.c -o $(OBJ_PATH)/parser_utils.o

# ================================== RENDER  ==================================

$(OBJ_PATH)/cube.o: $(SRC_PATH)/cube.c $(SRC_PATH)/cube.h \
	$(SRC_PATH)/minimap.h $(SRC_PATH)/parser.h $(SRC_PATH)/error.h \
	$(LIBFT_PATH)/libft.h $(VECTOR_PATH)/vector.h \
	$(MLX_DIR)/include/MLX42/MLX42.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_PATH)/cube.c -o $(OBJ_PATH)/cube.o

$(OBJ_PATH)/player.o: $(SRC_PATH)/player.c $(SRC_PATH)/cube.h \
	$(LIBFT_PATH)/libft.h $(VECTOR_PATH)/vector.h \
	$(MLX_DIR)/include/MLX42/MLX42.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_PATH)/player.c -o $(OBJ_PATH)/player.o

$(OBJ_PATH)/player2.o: $(SRC_PATH)/player2.c $(SRC_PATH)/cube.h \
	$(LIBFT_PATH)/libft.h $(VECTOR_PATH)/vector.h \
	$(MLX_DIR)/include/MLX42/MLX42.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_PATH)/player2.c -o $(OBJ_PATH)/player2.o

$(OBJ_PATH)/error.o: $(SRC_PATH)/error.c $(SRC_PATH)/error.h \
	$(LIBFT_PATH)/libft.h $(VECTOR_PATH)/vector.h \
	$(MLX_DIR)/include/MLX42/MLX42.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_PATH)/error.c -o $(OBJ_PATH)/error.o


# ================================= MINIMAP  ==================================

$(OBJ_PATH)/minimap.o: $(SRC_PATH)/minimap.c $(SRC_PATH)/minimap.h \
	$(SRC_PATH)/cube.h \
	$(LIBFT_PATH)/libft.h $(VECTOR_PATH)/vector.h \
	$(MLX_DIR)/include/MLX42/MLX42.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/minimap.c -o $(OBJ_PATH)/minimap.o

$(OBJ_PATH)/minimap_walls.o: $(SRC_PATH)/minimap_walls.c $(SRC_PATH)/minimap.h \
	$(SRC_PATH)/cube.h \
	$(LIBFT_PATH)/libft.h $(VECTOR_PATH)/vector.h \
	$(MLX_DIR)/include/MLX42/MLX42.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/minimap_walls.c -o $(OBJ_PATH)/minimap_walls.o

$(OBJ_PATH)/minimap_utils.o: $(SRC_PATH)/minimap_utils.c $(SRC_PATH)/minimap.h \
	$(SRC_PATH)/cube.h \
	$(LIBFT_PATH)/libft.h $(VECTOR_PATH)/vector.h \
	$(MLX_DIR)/include/MLX42/MLX42.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/minimap_utils.c -o $(OBJ_PATH)/minimap_utils.o

# ================================== GRAPHX ===================================

$(OBJ_PATH)/graphx_utils.o: $(SRC_PATH)/graphx_utils.c $(SRC_PATH)/graphx.h \
	$(LIBFT_PATH)/libft.h $(VECTOR_PATH)/vector.h \
	$(MLX_DIR)/include/MLX42/MLX42.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/graphx_utils.c -o $(OBJ_PATH)/graphx_utils.o

$(OBJ_PATH)/graphx_line.o: $(SRC_PATH)/graphx_line.c $(SRC_PATH)/graphx.h \
	$(LIBFT_PATH)/libft.h $(VECTOR_PATH)/vector.h \
	$(MLX_DIR)/include/MLX42/MLX42.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/graphx_line.c -o $(OBJ_PATH)/graphx_line.o

$(OBJ_PATH)/graphx_line_thick.o: $(SRC_PATH)/graphx_line_thick.c \
	$(SRC_PATH)/graphx.h \
	$(LIBFT_PATH)/libft.h $(VECTOR_PATH)/vector.h \
	$(MLX_DIR)/include/MLX42/MLX42.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/graphx_line_thick.c -o $(OBJ_PATH)/graphx_line_thick.o

$(OBJ_PATH)/graphx_polygon.o: $(SRC_PATH)/graphx_polygon.c \
	$(SRC_PATH)/graphx.h \
	$(LIBFT_PATH)/libft.h $(VECTOR_PATH)/vector.h \
	$(MLX_DIR)/include/MLX42/MLX42.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/graphx_polygon.c -o $(OBJ_PATH)/graphx_polygon.o

$(OBJ_PATH)/graphx_polygon2.o: $(SRC_PATH)/graphx_polygon2.c \
	$(SRC_PATH)/graphx.h \
	$(LIBFT_PATH)/libft.h $(VECTOR_PATH)/vector.h \
	$(MLX_DIR)/include/MLX42/MLX42.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) \
	-c $(SRC_PATH)/graphx_polygon2.c -o $(OBJ_PATH)/graphx_polygon2.o

$(OBJ_PATH)/graphx_circle.o: $(SRC_PATH)/graphx_circle.c \
	$(SRC_PATH)/graphx.h \
	$(LIBFT_PATH)/libft.h $(VECTOR_PATH)/vector.h \
	$(MLX_DIR)/include/MLX42/MLX42.h
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
