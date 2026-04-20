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

SRCS=main.c
OBJS=$(OBJ_PATH)/main.o

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

$(LIBFT_A):
	$(MAKE) -C $(LIBFT_PATH)

$(VECTOR_A):
	$(MAKE) -C $(VECTOR_PATH)

$(MLX_A):
	cmake -B $(MLX_BUILD_DIR) $(MLX_DEBUG) $(MLX_DIR)
	cmake --build $(MLX_BUILD_DIR) -j$(shell nproc --all)

# Here we build all source files manually
$(OBJ_PATH)/main.o: $(SRC_PATH)/main.c $(LIBFT_PATH)/libft.h \
	$(VECTOR_PATH)/vector.h $(MLX_DIR)/include/MLX42/MLX42.h
	mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) $(INCLUDES) -c $(SRC_PATH)/main.c -o $(OBJ_PATH)/main.o

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
