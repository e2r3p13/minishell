# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/12 15:15:55 by lfalkau           #+#    #+#              #
#    Updated: 2020/03/25 20:54:35 by lfalkau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCS_PATH = ./includes/
SRCS_PATH = ./srcs/
OBJS_PATH = ./objs/
OBJB_PATH = ./objs/builtins
LBFT_PATH = ./libft/libft.a
RSCS_PATH = /tmp/
GDDS_NAME = ipt_git_prompt.sh
BTNS_PATH = ./builtins/

SRCS =	main.c \
		minishell.c \
		ipt_prompt.c \
		utils.c \
		ipt_cmd_get.c \
		ipt_cmd_edit.c \
		ipt_cmd_history.c \
		lex_main.c \
		lex_tokens.c \
		termios_utils.c \
		exe_main.c \
		tmp_exec.c \
		builtins/cd.c \
		builtins/echo.c \
		builtins/env.c \
		builtins/pwd.c \
		builtins/exit.c \
		expand.c \
		signals.c

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
	@mkdir -p $(OBJB_PATH)
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
