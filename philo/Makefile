NAME = philo
BONUS_NAME = philo_bonus

DIR_ACTIVITIES = ./activities/
SRCS_ACTIVITIES = death.c philo_activities.c
DIR_PRINTS = ./prints/
SRCS_PRINTS = print_gate.c print_statements.c
DIR_ROUTINE = ./routine/
SRCS_ROUTINE = routine.c
DIR_UTILS = ./utils/
SRCS_UTILS = time.c utils.c
DIR_OTHER = ./
SRCS_OTHER = init.c main.c

SRCS = $(addprefix $(DIR_ACTIVITIES), $(SRCS_ACTIVITIES)) \
		$(addprefix $(DIR_PRINTS), $(SRCS_PRINTS)) \
		$(addprefix $(DIR_ROUTINE), $(SRCS_ROUTINE)) \
		$(addprefix $(DIR_UTILS), $(SRCS_UTILS)) \
		$(addprefix $(DIR_OTHER), $(SRCS_OTHER))

SRCS_NO_PATH = $(SRCS_ACTIVITIES) $(SRCS_PRINTS) $(SRCS_ROUTINE) $(SRCS_UTILS) $(SRCS_OTHER)

B_SRCS = $(SRCS)
##MAIN_SRCS = $(addprefix ./philo/, $(SRCS))
MAIN_SRCS = $(SRCS)
OBJ_DIR = ./obj/

OBJS = $(addprefix $(OBJ_DIR), $(SRCS_NO_PATH:.c=.o))

B_OBJS = $(addprefix $(OBJ_DIR), $(B_SRCS:.c=.o))

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)
	@echo "all DONE"

$(NAME): ${OBJ_DIR} $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ${NAME}

bonus: ${OBJ_DIR} $(B_OBJS)
	$(CC) $(CFLAGS) $(B_OBJS) -o ${BONUS_NAME}

$(OBJ_DIR)%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -g -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "OBJ_DIR DONE"

clean:
	rm -f $(OBJS) $(B_OBJS)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
