NAME = libftprintf.a

# Folders
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include

# Source and object files
SRC_FILES = $(notdir $(wildcard $(SRC_DIR)/*.c))
OBJ_FILES = $(SRC_FILES:.c=.o)
SRCS = $(wildcard $(SRC_DIR)/*.c)
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
	# Add rules for bonus compilation if needed.

debug: CFLAGS += -g
debug: all
	# Add rules for debug compilation if needed.

.PHONY: all clean fclean re bonus debug

