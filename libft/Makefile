CC=cc
NAME=libft.a
CFLAGS=-Wall -Werror -Wextra -g3 -O0

MAIN_SRCS=ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
	 ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
	 ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_strchr.c \
	 ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
	 ft_atoi.c ft_calloc.c ft_realloc.c ft_strdup.c ft_substr.c ft_strjoin.c \
	 ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
	 ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	 get_next_line.c get_next_line_utils.c \
	 ft_getpid.c ft_getppid.c ft_getuid.c ft_getgid.c ft_getpwuid.c ft_getpwuid_aux.c \
	 ft_abs.c ft_isnum.c \
	 ft_aux.c
	 
BONUS_SRCS=ft_lstnew_bonus.c ft_lstsize_bonus.c ft_lstadd_front_bonus.c \
	ft_lstlast_bonus.c ft_lstadd_back_bonus.c ft_lstdelone_bonus.c \
	ft_lstclear_bonus.c ft_lstiter_bonus.c ft_lstmap_bonus.c

MAIN_OBJS=ft_isalpha.o ft_isdigit.o ft_isalnum.o ft_isascii.o ft_isprint.o \
	 ft_strlen.o ft_memset.o ft_bzero.o ft_memcpy.o ft_memmove.o \
	 ft_strlcpy.o ft_strlcat.o ft_toupper.o ft_tolower.o ft_strchr.o \
	 ft_strrchr.o ft_strncmp.o ft_memchr.o ft_memcmp.o ft_strnstr.o \
	 ft_atoi.o ft_calloc.o ft_realloc.o ft_strdup.o ft_substr.o ft_strjoin.o \
	 ft_strtrim.o ft_split.o ft_itoa.o ft_strmapi.o ft_striteri.o \
	 ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o \
	 get_next_line.o get_next_line_utils.o \
	 ft_getpid.o ft_getppid.o ft_getuid.o ft_getgid.o ft_getpwuid.o ft_getpwuid_aux.o \
	 ft_abs.o ft_isnum.o \
	 ft_aux.o

BONUS_OBJS=ft_lstnew_bonus.o ft_lstsize_bonus.o ft_lstadd_front_bonus.o \
	ft_lstlast_bonus.o ft_lstadd_back_bonus.o ft_lstdelone_bonus.o \
	ft_lstclear_bonus.o ft_lstiter_bonus.o ft_lstmap_bonus.o

$(NAME) : $(MAIN_OBJS)
	ar rcs $(NAME) $(MAIN_OBJS)

bonus : $(BONUS_OBJS)
	ar rcs $(NAME) $(BONUS_OBJS)

all : $(NAME)

clean :
	rm -rf $(MAIN_OBJS) $(BONUS_OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

%.o : %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: all bonus clean fclean re
