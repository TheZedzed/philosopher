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

NAME		:= philo_bonus
CC			:= gcc
CFLAGS		:= -Wall -Wextra -Werror
CPPFLAGS	:= -I./include_bonus
LDLIBS		:= -lpthread
SRCS		:= $(addsuffix _bonus.c, $(addprefix srcs_bonus/, main init dinner))
OBJS 		:= $(SRCS:.c=.o)

.Phony: all re clean fclean bonus

all: $(NAME)

bonus:
	make

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDLIBS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
