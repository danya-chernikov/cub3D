CC=cc
NAME=libvector.a
CFLAGS=-Wall -g3 -O0

SRCS=vector_main.c vector_access.c vector_info.c \
	 vector_si.c vector_msi.c vector_stack.c vector_stack2.c \
	 vector_settings.c vector_print.c vector_utility.c

OBJS=vector_main.o vector_access.o vector_info.o \
	 vector_si.o vector_msi.o vector_stack.o vector_stack2.o \
	 vector_settings.o vector_print.o vector_utility.o

$(NAME) : $(OBJS)
	ar rcs $(NAME) $(OBJS)

all : $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

vector_main.o : vector_main.c vector.h
	$(CC) $(CFLAGS) -c vector_main.c

vector_access.o : vector_access.c vector.h
	$(CC) $(CFLAGS) -c vector_access.c

vector_info.o : vector_info.c vector.h
	$(CC) $(CFLAGS) -c vector_info.c

vector_si.o : vector_si.c vector.h
	$(CC) $(CFLAGS) -c vector_si.c

vector_msi.o : vector_msi.c vector.h
	$(CC) $(CFLAGS) -c vector_msi.c

vector_stack.o : vector_stack.c vector.h
	$(CC) $(CFLAGS) -c vector_stack.c

vector_stack2.o : vector_stack2.c vector.h
	$(CC) $(CFLAGS) -c vector_stack2.c

vector_settings.o : vector_settings.c vector.h
	$(CC) $(CFLAGS) -c vector_settings.c

vector_print.o : vector_print.c vector.h
	$(CC) $(CFLAGS) -c vector_print.c

vector_utility.o : vector_utility.c vector.h
	$(CC) $(CFLAGS) -c vector_utility.c

.PHONY: all clean fclean re
