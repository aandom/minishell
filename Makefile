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
OBJ_DIR = obj
SRC_DIR = srcs
B_SRC = srcs/builtin
E_SRC = srcs/execution
P_SRC = srcs/parsing
T_SRC = srcs/tokenize
U_SRC = srcs/utils

SRC = 	$(B_SRC)/builtins.c $(B_SRC)/envar.c $(B_SRC)/ft_cd.c $(B_SRC)/ft_echo.c $(B_SRC)/ft_exit.c $(B_SRC)/ft_export.c  $(B_SRC)/ft_new_env.c $(B_SRC)/ft_shlvl.c \
        $(B_SRC)/env_pointer.c $(B_SRC)/envar_utils.c $(B_SRC)/ft_cd_utils.c $(B_SRC)/ft_env.c $(B_SRC)/ft_exit_utils.c $(B_SRC)/ft_export_utils.c $(B_SRC)/ft_pwd.c $(B_SRC)/ft_unset.c \
		$(E_SRC)/execute.c $(E_SRC)/execute_fin_cmd.c $(E_SRC)/execute_utils.c $(E_SRC)/ft_pipe.c $(E_SRC)/ft_wait.c $(E_SRC)/iofds.c \
		$(P_SRC)/command.c $(P_SRC)/command_utils.c $(P_SRC)/command_arg.c $(P_SRC)/expand.c $(P_SRC)/expand_utils.c $(P_SRC)/expand_var.c $(P_SRC)/expand_var_utils.c $(P_SRC)/ft_heredoc.c \
		$(P_SRC)/ft_heredoc_delim.c $(P_SRC)/ft_heredoc_utils.c $(P_SRC)/ft_input.c $(P_SRC)/ft_iofds.c $(P_SRC)/ft_output.c $(P_SRC)/parser.c $(P_SRC)/quote.c $(P_SRC)/quote_utils.c \
		$(T_SRC)/ft_token.c $(T_SRC)/ft_token_utils.c \
		$(U_SRC)/clean_cmd.c $(U_SRC)/clean_token.c $(U_SRC)/error.c $(U_SRC)/exit_shell.c $(U_SRC)/ft_free.c $(U_SRC)/ft_strcmp.c $(U_SRC)/signals.c $(U_SRC)/signals_2.c \
		$(SRC_DIR)/main.c

CFLAGS = -Wall -Wextra -Werror
READLINE= -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include
CC = cc -I/usr/local/opt/readline/include

OBJS = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJS = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(@D)
	@${CC} ${CFLAGS} -c $< -o $@

all: $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJ_DIR) $(OBJS)
		 @$(MAKE) --no-print-directory -C ./libft/
		 @$(CC) $(CFLAGS) $(OBJS) $(READLINE) libft/libft.a  -o $(NAME)
		 @echo "minishell is complied!$(DEFAULT)"

leaks: 
	valgrind --suppressions=readleak.txt --leak-check=full --trace-children=yes \
	--show-leak-kinds=all --track-origins=yes --track-fds=yes ./minishell

clean: 
		@$(MAKE) --no-print-directory clean -C ./libft/
		@rm -f $(OBJS)
		@echo "$-------- src objects files removed $(DEFAULT)" 
		@rm -rf $(OBJ_DIR)

fclean: clean
		@rm -f libft/libft.a
		@rm -f $(NAME)
		@echo "$(NAME) Removed!$(DEFAULT)"

re: fclean	all

# .SILENT:

.PHONY: all clean fclean re