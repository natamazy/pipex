# Project name
NAME = pipex

# Compilator
CC = cc
# Compilator flags
CFLAGS = -Wall -Wextra -Werror #-g3 -fsanitize=address

# Headers
HEADERS = includes/pipex.h

# Source directory
SRCS_DIR = utilities/
# Objects directory
OBJS_DIR = objects/

# Source file names
SRCS_NAME = main.c \
			utilities_1.c \
			utilities_2.c \
			utilities_3.c \
			utilities_4.c \
			get_next_line.c \
			get_next_line_utils.c \
			ft_split.c \
			ft_strjoin.c \
			ft_substr.c \
			parent_child.c

# Objects file names
OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
OBJS_NAME = $(SRCS_NAME:.c=.o)

# Compilation process
all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c $(HEADERS) Makefile
	$(CC) $(CFLAGS) -c $< -o $@

# Cleaning
clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

# Remaking
re: clean all

# PHONY files
.PHONY: all clean fclean re
