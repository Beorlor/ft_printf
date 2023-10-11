NAME = libftprintf.a

# Folders
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Source and object files
SRC_FILES = ft_parsing.c ft_print_di.c ft_print_p.c ft_print_xX.c \
            ft_print_cs.c ft_printf.c ft_print_u.c ft_utils.c
OBJ_FILES = $(SRC_FILES:.c=.o)
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INC_FLAGS = -I$(INC_DIR)

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: all

.PHONY: all clean fclean re bonus
