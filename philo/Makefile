# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/27 02:09:10 by jgoldste          #+#    #+#              #
#    Updated: 2022/05/28 00:31:30 by jgoldste         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

SRCS		=	philo.c		validation.c	init.c		launch.c	living.c\
				utils.c		error.c

HEADER		=	philo.h

OBJS		=	$(patsubst %.c,%.o,$(SRCS))

D_FILES		=	$(patsubst %.c,%.d,$(SRCS))

INCLUDES	=	-I.

CFLAGS		=	-Wall -Wextra -Werror -g# -fsanitize=thread

CC			=	gcc

RM			=	rm -rf

YELLOW		=	"\033[1;33m"
GREEN		=	"\033[1;32m"
END			=	"\033[0m"

.PHONY		:	all clean fclean re

all			:	$(NAME)

%.o			:	%.c $(HEADER)
				$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@ -MD

$(NAME)		:	$(OBJS)
				$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS)
				@echo ${GREEN} "\n\tPhilosophers is compiled\n" ${END}

clean		:	
				@$(RM) $(OBJS) $(D_FILES)
				@echo ${YELLOW} "\n\tPhilosophers 'clean' status: DONE\n" ${END}
				
fclean		:	clean
				@$(RM) $(NAME)
				@echo ${YELLOW} "\n\tPhilosophers 'fclean' status: DONE\n" ${END}

re			:	fclean all
