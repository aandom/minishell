# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/19 11:00:00 by aandom            #+#    #+#              #
#    Updated: 2023/08/13 03:33:30 by aandom           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= libft.a

SRCS 		= 	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isdigit.c ft_isspace.c ft_itoa.c ft_memchr.c \
				ft_memcpy.c ft_memset.c ft_putendl_fd.c ft_putstr_fd.c ft_split_utils.c ft_split.c ft_strchr.c ft_strdup.c  \
				ft_strjoin.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strrchr.c ft_strtrim.c ft_substr.c 
				
OBJECTS		= $(SRCS:.c=.o)
RM			= rm -f
LIBCREATE	= ar -rcs		
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror

%.o: %.c 
		@${CC} ${CFLAGS} -c $< -o $@

$(NAME): $(OBJECTS)
	@$(LIBCREATE) $(NAME) $(OBJECTS)
	@echo "+++++++ libft is complied!$(DEFAULT)"

all : $(NAME)

clean :
	@$(RM) $(OBJECTS)
	@echo "$-------- libft objects files removed $(DEFAULT)" 

fclean : clean
	@$(RM) $(NAME)
	@echo "-------- $(NAME) removed $(DEFAULT)" 

re : fclean all

.PHONY: all clean fclean re