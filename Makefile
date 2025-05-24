NAME        = philo
BONUS_NAME  = philo_bonus

CC          = cc
INCLUDE     = -I./include
CFLAGS = -g -Wall -Wextra -Werror $(INCLUDE) #-fsanitize=thread

SRC_DIR     = src
OBJ_DIR     = obj

BONUS_SRC_DIR = bonus_src
BONUS_OBJ_DIR = bonus_obj

SRC_FILES = main.c routine.c philo_init.c philo_utils.c

BONUS_SRC_FILES = 

SRC        = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ        = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

BONUS_SRC  = $(addprefix $(BONUS_SRC_DIR)/, $(BONUS_SRC_FILES))
BONUS_OBJ  = $(addprefix $(BONUS_OBJ_DIR)/, $(BONUS_SRC_FILES:.c=.o))

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

$(BONUS_NAME): mlx lib $(BONUS_OBJ)
	$(CC) $(CFLAGS) $(BONUS_OBJ) -o $(BONUS_NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(BONUS_SRC_DIR)/%.c | $(BONUS_OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(BONUS_OBJ_DIR):
	mkdir -p $(BONUS_OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR) $(BONUS_OBJ_DIR)

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all bonus clean fclean re
