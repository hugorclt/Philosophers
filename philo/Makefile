# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hrecolet <hrecolet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/26 12:15:45 by hrecolet          #+#    #+#              #
#    Updated: 2022/02/25 11:19:00 by hrecolet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	srcs/main.c srcs/check.c srcs/init.c srcs/routine.c\
				srcs/utils1.c srcs/utils2.c

INCL		=	philo.h

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

RM			=	rm -f

NAME		=	philo

OBJ			=	$(SRCS:.c=.o)

all			:	$(NAME) 


$(NAME)		:	$(OBJ) philo.h 
				$(CC) $(CFLAGS) $(OBJ) $(INCL) -pthread -o $(NAME) 
		
clean		:	
				$(RM) $(OBJ) $(OBJ_BONUS)

fclean		:	clean
				$(RM) $(NAME) $(BONUS_NAME) $(OBJ_BONUS)

re			:	fclean all

.PHONY		:	clean fclean re all
