# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/12 15:15:55 by lfalkau           #+#    #+#              #
#    Updated: 2020/01/17 12:02:45 by lfalkau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCS_PATH = ./includes/
SRCS_PATH = ./srcs/
OBJS_PATH = ./objs/
LIBFT_A = ./libft/libft.a
LIBFT_M = ./libft/

SRCS =	main.c \
		minishell.c \
		prompt.c \
		utils.c

TMP = $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJS_PATH),$(TMP))

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
OFLAGS = -g3 -fsanitize=address

all: aff_h $(NAME) aff_e

$(NAME): $(OBJS)
	@make -C $(LIBFT_M)
	@make aff_b
	@$(CC) $(CFLAGS) -I $(INCS_PATH) $(OBJS) $(LIBFT_A) -o $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c includes/minishell.h
	@mkdir -p $(OBJS_PATH)
	@$(CC) $(CFLAGS) -I $(INCS_PATH) -c $< -o $@

clean:
	@rm -rf $(OBJS_PATH)
	@make fclean -C ./libft/

fclean: clean
	@rm -rf $(NAME)

re: fclean all

aff_h:
	@printf "\n"
	@printf " _____ _     _     _       _ _ \n"
	@printf "|     |_|___|_|___| |_ ___| | |\n"
	@printf "| | | | |   | |_ -|   | -_| | |\n"
	@printf "|_|_|_|_|_|_|_|___|_|_|___|_|_|\n"
	@printf "\n"

aff_b:
	@printf "● Minishell "

aff_e:
	@printf "\033[32m✓\033[0m\n"
