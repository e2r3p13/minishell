# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/12 15:15:55 by lfalkau           #+#    #+#              #
#    Updated: 2020/04/10 16:13:27 by lfalkau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCS_PATH = ./includes/
SRCS_PATH = ./srcs/
OBJS_PATH = ./objs/
LBFT_PATH = ./libft/libft.a
RSCS_PATH = /tmp/

SRCS =	main.c \
		minishell.c \
		env_0.c \
		env_1.c \
		input/prompt.c \
		input/get_input.c \
		input/bind_spe.c \
		input/bind_arrows.c \
		input/bind_ctrl.c \
		input/term_utils.c \
		input/bind_tabulation_0.c \
		input/bind_tabulation_1.c \
		input/history.c \
		lexer/lexer.c \
		lexer/lexer_utils.c \
		lexer/tokenize.c \
		lexer/expand.c \
		lexer/expand_quote.c \
		lexer/expand_wcard.c \
		parser/parser.c \
		execution/execute.c \
		execution/redirect.c \
		execution/tweak.c \
		builtins/cd.c \
		builtins/echo.c \
		builtins/unset.c \
		builtins/export.c \
		builtins/env.c \
		builtins/pwd.c \

CC = gcc
CFLAGS = -Wall -Wextra -Werror
OFLAGS = -g3 -fsanitize=address

TMP = $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJS_PATH),$(TMP))

NAME = minishell

all: $(NAME)

$(NAME): move_script $(OBJS)
	make -C ./libft/
	$(CC) $(CFLAGS) -I $(INCS_PATH) $(OBJS) $(LBFT_PATH) -o $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c includes/minishell.h
	@mkdir -p $(OBJS_PATH)
	@mkdir -p ./objs/input
	@mkdir -p ./objs/lexer
	@mkdir -p ./objs/parser
	@mkdir -p ./objs/execution
	@mkdir -p ./objs/builtins
	$(CC) $(CFLAGS) -I $(INCS_PATH) -c $< -o $@

clean:
	@rm -rf $(OBJS_PATH)
	@make fclean -C ./libft/

fclean: clean
	@rm -f $(NAME)

re: fclean all

move_script:
	cp $(SRCS_PATH)git_prompt.sh /tmp/git_prompt.sh
