# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: azeraoul <azeraoul@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/02 19:28:07 by azeraoul          #+#    #+#              #
#    Updated: 2021/09/22 23:20:31 by azeraoul         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo
CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:= -I./include
LDLIBS		:= -lpthread
SRCS		:= $(addprefix srcs/, main.c dinner.c init.c)
OBJS 		:= $(SRCS:.c=.o)

.Phony: all re clean fclean

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
