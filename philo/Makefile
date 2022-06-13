# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfranca- <lfranca-@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/01 20:32:43 by lfranca-          #+#    #+#              #
#    Updated: 2022/06/13 09:18:55 by lfranca-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc

CFLAGS = -g -Wall -Wextra -Werror -fsanitize=thread

SRC = src/has_died.c src/init.c src/main.c src/philo_utils.c src/routine.c 

OBJS = $(SRC:.c=.o)

INC = -I inc/

RM = rm -rf

all: $(NAME)

$(NAME): $(OBJS)
	@echo done!!
	@$(CC) $(CFLAGS) $(OBJS) $(INC) -pthread -o philo

clean:
	@$(RM) $(OBJS)
	@echo "Clean done!"
	
fclean: clean
	@$(RM) $(NAME)
	@echo "Binary files and objects deleted!"

re: fclean all

.PHONY: all clean fclean re
