NAME = philo
BONUS_NAME = philo_bonus

SRCS =
B_SRCS = $(SRCS)
MAIN_SRCS = $(SRCS)
OBJ_DIR = ./obj/

OBJS = $(addprefix $(OBJ_DIR), $(MAIN_SRCS:.c=.o))

B_OBJS = $(addprefix $(OBJ_DIR), $(B_SRCS:.c=.o))

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)
	@echo "all DONE"

$(NAME): ${OBJ_DIR} $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) ${NAME}

$(BONUS_NAME): bonus

bonus: ${OBJ_DIR} $(B_OBJS)
	$(CC) $(CFLAGS) $(B_OBJS) ${BONUS_NAME}

$(OBJ_DIR)%.o: %.c | obj
	$(CC) $(CFLAGS) -g -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "OBJ_DIR DONE"

clean:
	rm -f $(OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re
