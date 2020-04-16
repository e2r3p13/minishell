# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/12 15:15:55 by lfalkau           #+#    #+#              #
#    Updated: 2020/04/16 14:29:21 by lfalkau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCS_PATH = ./includes/
SRCS_PATH = ./srcs/
OBJS_PATH = ./objs/
LBFT_PATH = ./libft/libft.a
RSCS_PATH = /tmp/

HDRS =	keys.h \
		minishell.h \
		tokens.h \
		../libft/includes/libft.h \

SRCS =	main.c \
		minishell.c \
		env_0.c \
		env_1.c \
		alias_0.c \
		input/prompt.c \
		input/get_input.c \
		input/bind_spe.c \
		input/bind_arrows.c \
		input/bind_ctrl_0.c \
		input/bind_ctrl_1.c \
		input/term_utils.c \
		input/bind_tabulation_0.c \
		input/bind_tabulation_1.c \
		input/history_0.c \
		input/history_1.c \
		lexer/lexer.c \
		lexer/lexer_utils.c \
		lexer/lexer_alias.c \
		lexer/tokenize.c \
		lexer/expand.c \
		lexer/expand_quote.c \
		lexer/expand_wcard_0.c \
		lexer/expand_wcard_1.c \
		parser/ast_create.c \
		parser/ast_utils.c \
		builtins/cd.c \
		builtins/echo.c \
		builtins/unset.c \
		builtins/export.c \
		builtins/env.c \
		builtins/pwd.c \
		builtins/alias.c \
		builtins/unalias.c \
		execution/execute.c \
		execution/execute_command.c \
		execution/dgreat_redirection.c \
		execution/great_redirection.c \
		execution/less_redirection.c \
		execution/pipe_redirection.c \

CC = gcc
CFLAGS = -Wall -Wextra -Werror
OFLAGS = -g3 -fsanitize=address

TMP = $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJS_PATH),$(TMP))
INCS = $(addprefix $(INCS_PATH),$(HDRS))

NAME = minishell

all: $(NAME)

$(NAME): move_script start $(OBJS)
	@$(CC) $(CFLAGS) -I $(INCS_PATH) $(OBJS) $(LBFT_PATH) -o $(NAME) $(OFLAGS)
	@printf "\033[032m[DONE]\033[0m\n"

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(INCS)
	@$(CC) $(CFLAGS) -I $(INCS_PATH) -c $< -o $@
	@printf "━"

start:
	@make -C ./libft/
	@mkdir -p $(OBJS_PATH)
	@mkdir -p ./objs/input
	@mkdir -p ./objs/lexer
	@mkdir -p ./objs/parser
	@mkdir -p ./objs/execution
	@mkdir -p ./objs/builtins
	@printf "\033[093mCompiling minishell:\033[0m\n"

clean:
	@rm -rf $(OBJS_PATH)
	@make fclean -C ./libft/

fclean: clean
	@rm -f $(NAME)

re: fclean all

move_script:
	@cp $(SRCS_PATH)git_prompt.sh /tmp/git_prompt.sh
