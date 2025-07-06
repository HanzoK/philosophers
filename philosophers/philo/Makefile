NAME	= philo

CC		= cc

CFLAGS	= -Wall -Wextra -Werror

SRCS	= main.c \
		  edge_case_city.c \
		  fork_management.c \
		  freedom.c \
		  input_validation.c \
		  monitor_philos.c \
		  philosopher_actions.c \
		  philosopher_actions_utils.c \
		  philosopher_utils.c \
		  simulation_preparation.c \
		  run_simulation.c \
		  thread_management.c \
		  thread_routine.c \
		  time_validation.c

OBJ		= $(SRCS:%.c=%.o)

RM		= rm -rf

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re
