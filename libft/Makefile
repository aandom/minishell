# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aandom <aandom@student.abudhabi42.ae>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/19 11:00:00 by aandom            #+#    #+#              #
#    Updated: 2024/01/24 21:21:19 by aandom           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= libft.a

OBJDIR 		= obj

SRCS 		= 	ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isdigit.c ft_isspace.c ft_itoa.c ft_memchr.c \
				ft_memcpy.c ft_memset.c ft_putendl_fd.c ft_putstr_fd.c ft_split_utils.c ft_split.c ft_strchr.c ft_strdup.c  \
				ft_strjoin.c ft_strlcpy.c ft_strlen.c ft_strncmp.c ft_strrchr.c ft_strtrim.c ft_substr.c 
				
RM			= rm -f
LIBCREATE	= ar -rcs		
CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror
OBJECTS = $(patsubst %.c,$(OBJDIR)/%.o,$(notdir $(SRCS)))

$(OBJDIR)/%.o: %.c | $(OBJDIR)
	@mkdir -p $(@D)
	@${CC} ${CFLAGS} -c $< -o $@
	
all : $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(NAME): $(OBJDIR) $(OBJECTS)
	@$(LIBCREATE) $(NAME) $(OBJECTS)
	@echo "+++++++ libft is complied!$(DEFAULT)"

clean :
	@$(RM) $(OBJECTS)
	@$(RM) -r $(OBJDIR)
	@echo "$-------- libft objects files removed $(DEFAULT)" 

fclean : clean
	@$(RM) $(NAME)
	@echo "------- $(NAME) removed $(DEFAULT)" 

re : fclean all

.PHONY: all clean fclean re