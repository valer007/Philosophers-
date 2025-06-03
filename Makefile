NAME        = philo
BONUS_NAME  = philo_bonus

CC          = cc
INCLUDE     = -I./include
CFLAGS = -g -Wall -Wextra -Werror $(INCLUDE)

SRC_DIR     = src
OBJ_DIR     = obj

BONUS_SRC_DIR = bonus_src
BONUS_OBJ_DIR = bonus_obj

SRC_FILES = main.c routine.c philo_init.c philo_utils.c

BONUS_SRC_FILES = 

SRC        = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ        = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

all: $(NAME)

$(NAME): $(OBJ) Makefile
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
