# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jgoldste <jgoldste@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 06:28:38 by jgoldste          #+#    #+#              #
#    Updated: 2022/06/07 19:49:49 by jgoldste         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo_bonus

SRCS		=	philo_bonus.c	validation.c	init.c		utils.c		error.c\
				launch.c		living.c	

HEADER		=	philo_bonus.h

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
				@echo ${GREEN} "\n\tPhilosophers bonus is compiled\n" ${END}

clean		:	
				@$(RM) $(OBJS) $(D_FILES)
				@echo ${YELLOW} "\n\tPhilosophers bonus 'clean' status: DONE\n" ${END}
				
fclean		:	clean
				@$(RM) $(NAME)
				@echo ${YELLOW} "\n\tPhilosophers bonus 'fclean' status: DONE\n" ${END}

re			:	fclean all
