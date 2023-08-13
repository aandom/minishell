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

SRC = 	builtins.c command.c command_arg.c execute_fin_cmd.c command_utils.c env_pointer.c envar_utils.c\
		envar.c error.c execute.c execute_utils.c exit_shell.c expand.c expand_utils.c   \
		expand_var.c expand_var_utils.c free_iofds.c ft_cd.c ft_cd_utils.c \
		ft_echo.c ft_env.c ft_exit.c ft_exit_utils.c ft_export.c ft_export_utils.c \
		ft_free.c ft_free_new.c ft_heredoc.c ft_heredoc_utils.c  ft_heredoc_utils2.c ft_input.c ft_iofds.c \
		ft_output.c ft_pipe.c ft_pwd.c ft_shlvl.c ft_strcmp.c ft_token.c ft_token_utils.c \
		ft_unset.c ft_wait.c iofds.c lexer.c lexer_utils.c main.c parser.c signals.c \
		signals_2.c

OBJS =  $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
READLINE= -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
CC = cc -I/usr/local/opt/readline/include -g

%.o: %.c 
		${CC} ${CFLAGS} -c $< -o $@

$(NAME): $(OBJS)
		 @$(MAKE) -C ./libft/
		 $(CC) $(CFLAGS) $(OBJS) $(READLINE) libft/libft.a  -o $(NAME) 

leaks:
	valgrind --suppressions=readleak.txt \
	--leak-check=full --trace-children=yes \
	--show-leak-kinds=all --track-origins=yes \
	--track-fds=yes ./minishell

all: $(NAME)

clean: 
		@echo "$-------- CLEAN $(DEFAULT)"
		@$(MAKE) clean -C ./libft/
		rm -f $(OBJS)

fclean: clean
		@rm -f libft/libft.a
		rm -f $(NAME)
		@echo "$-------- $(NAME) Removed!$(DEFAULT)"

re: fclean	all

.PHONY: all clean fclean re