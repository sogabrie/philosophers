SRCS			=	philosophers.c cheack_inic_argv.c cheack_inic_argv_utils.c \
					initalizatia_mut.c start.c start_utils.c free_ret.c

OBJS			= $(SRCS:.c=.o)

CC				= cc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror

NAME			= philo_bonus


all:			$(NAME) Makefile philosophers.h

$(NAME):		$(OBJS)
				$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
