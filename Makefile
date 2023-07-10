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
SRC = $(wildcard *.c)
OBJS =  $(SRC:.c=.o)
CFLAGS = 
CC = cc

%.o: %.c 
		@${CC} ${CFLAGS} -c $< -o $@

$(NAME): $(OBJS)
		 $(CC) $(CFLAGS)  $(OBJS) -o $(NAME) -lreadline

all: $(NAME)

clean: 
		@echo "$-------- CLEAN $(DEFAULT)"
		rm -f $(OBJS)

fclean: clean 
		rm -f $(NAME)
		@echo "$-------- $(NAME) Removed!$(DEFAULT)"

re: fclean	all

.PHONY: all clean fclean re