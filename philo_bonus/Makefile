NAME = philo_bonus

DIR_ACTIVITIES = philo_activities/
SRCS_ACTIVITIES = death.c philo_activities.c fork_helpers.c
DIR_PRINTS = prints/
SRCS_PRINTS = print_gate.c print_statements.c
DIR_ROUTINE = routine/
SRCS_ROUTINE = routine.c
DIR_UTILS = utils/
SRCS_UTILS = time.c utils.c
DIR_CLEAN = clean/
SRCS_CLEAN = main_clean.c
DIR_GET_SET = get_set/
SRCS_GET_SET = order.c time.c
DIR_OTHER =
SRCS_OTHER = init.c main.c init_helper.c

SRCS = $(addprefix $(DIR_ACTIVITIES), $(SRCS_ACTIVITIES)) \
		$(addprefix $(DIR_PRINTS), $(SRCS_PRINTS)) \
		$(addprefix $(DIR_ROUTINE), $(SRCS_ROUTINE)) \
		$(addprefix $(DIR_UTILS), $(SRCS_UTILS)) \
		$(addprefix $(DIR_OTHER), $(SRCS_OTHER)) \
		$(addprefix $(DIR_CLEAN), $(SRCS_CLEAN)) \
		$(addprefix $(DIR_GET_SET), $(SRCS_GET_SET))

SRCS_NO_PATH = $(SRCS_ACTIVITIES) $(SRCS_PRINTS) $(SRCS_ROUTINE) $(SRCS_UTILS) $(SRCS_OTHER)

B_SRCS = $(SRCS)
##MAIN_SRCS = $(addprefix ./philo/, $(SRCS))
MAIN_SRCS = $(SRCS)
OBJ_DIR = ./obj/

INCLUDES_FLAG = -I .

SANITIZER = -g -fsanitize=thread

OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

B_OBJS = $(addprefix $(OBJ_DIR), $(B_SRCS:.c=.o))

CC = cc

CFLAGS = -Wall -Wextra -Werror $(INCLUDES_FLAG)

all: $(NAME)
	@echo "all DONE"

$(NAME): ${OBJ_DIR} $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o ${NAME}

bonus: ${OBJ_DIR} $(B_OBJS)
	$(CC) $(CFLAGS) $(B_OBJS) -o ${BONUS_NAME}

$(OBJ_DIR)%.o: %.c
	$(CC) $(CFLAGS) -g -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)
	mkdir -p $(OBJ_DIR)philo_activities
	mkdir -p $(OBJ_DIR)prints
	mkdir -p $(OBJ_DIR)routine
	mkdir -p $(OBJ_DIR)utils
	mkdir -p $(OBJ_DIR)clean
	mkdir -p $(OBJ_DIR)get_set
	@echo "OBJ_DIR DONE"

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re bonus
