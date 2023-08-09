# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 16:35:02 by aandom            #+#    #+#              #
#    Updated: 2023/06/05 21:19:34 by aandom           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = $(wildcard *.c) $(wildcard ./exec/builtins/*.c)
OBJS =  $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
READLINE = -lreadline -L /usr/local/Cellar/readline/8.1/lib -L /usr/local/Cellar/readline/8.1/include
READLINE_2 = -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
CC = cc -I/usr/local/opt/readline/include -g

%.o: %.c 
		@${CC} ${CFLAGS} -c $< -o $@

$(NAME): $(OBJS)
		 $(CC) $(CFLAGS)  $(OBJS) $(READLINE_2) -o $(NAME)

leaks:
	valgrind --suppressions=readleak.txt \
	--leak-check=full --trace-children=yes \
	--show-leak-kinds=all --track-origins=yes \
	--track-fds=yes ./minishell

all: $(NAME)

clean: 
		@echo "$-------- CLEAN $(DEFAULT)"
		rm -f $(OBJS)

fclean: clean 
		rm -f $(NAME)
		@echo "$-------- $(NAME) Removed!$(DEFAULT)"

re: fclean	all

.PHONY: all clean fclean re

