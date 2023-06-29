CC = @gcc
CFLAGS = -Wall -Wextra -Werror -I ./srcs/minishell.h
RM = @rm -rf
LIB_DIR = ./utils/libft
LIB = libft.a
NAME = minishell

UTL_DIR =	utils
UTL_FILES =	\
			ft_node_add_front.c \
			minisplit.c \
			tokenizer.c 
UTL =	$(addprefix $(UTL_DIR)/, $(UTL_FILES))

SRC_DIR =	./srcs
SRC_FILES =	\
			free_loop.c \
			ft_error.c \
			ft_free_everything.c \
			lexer.c \
			ft_struct_init.c \
			parsing.c \
			main.c
SRC =	$(UTL) $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OBJ_DIR = ./objs
OBJ =	$(addprefix $(OBJ_DIR)/, $(UTL:.c=.o)) $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))


all: $(OBJ_DIR)/$(UTL_DIR) $(NAME)

$(OBJ_DIR)/$(UTL_DIR):
	@mkdir -p $@

$(NAME): $(OBJ) $(LIB_DIR)/$(LIB)
	@echo "Compiling Executable"
	$(CC) $(CFLAGS) $(LIB_DIR)/$(LIB) -o $(NAME) $(OBJ) -lreadline

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/$(UTL_DIR)/%.o: $(UTL_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_DIR)/$(LIB):
	@make -C $(LIB_DIR)

clean:
	@echo "Removing Objects"
	$(RM) $(OBJ) $(OBJ_DIR)

fclean: clean
	@echo "Removing Executable"
	$(RM) $(NAME)
	@make fclean -C $(LIB_DIR)

re: fclean all

.PHONY: all clean fclean re
