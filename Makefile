# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/12 15:15:55 by lfalkau           #+#    #+#              #
#    Updated: 2020/03/28 22:46:54 by lfalkau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCS_PATH = ./includes/
SRCS_PATH = ./srcs/
OBJS_PATH = ./objs/
LBFT_PATH = ./libft/libft.a
RSCS_PATH = /tmp/
GDDS_NAME = /git_prompt.sh
BTNS_PATH = ./builtins/

SRCS =	main/main.c \
		main/minishell.c \
		input/prompt.c \
		input/command_0.c \
		input/command_1.c \
		input/command_2.c \
		input/command_3.c \
		input/history.c \
		input/utils.c \
		lexer/lexer.c \
		lexer/tokenize.c \
		lexer/expand.c \
		lexer/utils.c \
		execution/execute.c \
		builtins/cd.c \
		builtins/echo.c \
		builtins/env.c \
		builtins/pwd.c \
		builtins/exit.c \
		signals.c \
		utils.c

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
OFLAGS = -g3 -fsanitize=address

TMP = $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJS_PATH),$(TMP))

NAME = minishell

all: aff_h $(NAME) move_script

$(NAME): $(OBJS)
	@make -C ./libft/
	@printf "● minishell "
	@$(CC) $(CFLAGS) -I $(INCS_PATH) $(OBJS) $(LBFT_PATH) -o $(NAME)
	@printf "\033[32m✓\033[0m\n"
	@mkdir -p $(BTNS_PATH)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c includes/minishell.h
	@mkdir -p $(OBJS_PATH)
	@mkdir -p ./objs/main
	@mkdir -p ./objs/input
	@mkdir -p ./objs/lexer
	@mkdir -p ./objs/parser
	@mkdir -p ./objs/execution
	@mkdir -p ./objs/builtins
	@$(CC) -D GDD_PATH=\"$(RSCS_PATH)$(GDDS_NAME)\" $(CFLAGS) -I $(INCS_PATH) -c $< -o $@

clean:
	@rm -rf $(OBJS_PATH)
	@make fclean -C ./libft/

fclean: clean
	@rm -f $(NAME)
	@rm -rf $(BTNS_PATH)
	@rm -f $(RSCS_PATH)$(GDDS_NAME)
	@rm -f $(RSCS_PATH)/history

re: fclean all

aff_h:
	@printf "\n"
	@printf " _____ _     _     _       _ _ \n"
	@printf "|     |_|___|_|___| |_ ___| | |\n"
	@printf "| | | | |   | |_ -|   | -_| | |\n"
	@printf "|_|_|_|_|_|_|_|___|_|_|___|_|_|\n"
	@printf "\n"

move_script:
	@cp $(SRCS_PATH)$(GDDS_NAME) $(RSCS_PATH)
	@touch $(RSCS_PATH)/history
