# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/12 15:15:55 by lfalkau           #+#    #+#              #
#    Updated: 2020/01/18 16:45:20 by lfalkau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCS_PATH = ./includes/
SRCS_PATH = ./srcs/
OBJS_PATH = ./objs/
LIB_PATH = ./libft/libft.a

SRCS =	main.c \
		minishell.c \
		prompt.c \
		utils.c

CC = gcc
CFLAGS = -Wall -Wextra -Werror
OFLAGS = -g3 -fsanitize=address

TMP = $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJS_PATH),$(TMP))

NAME = minishell

all: aff_h $(NAME) aff_e move_script

$(NAME): $(OBJS)
	@make -C ./libft/
	@make aff_b
	@$(CC) $(CFLAGS) -I $(INCS_PATH) $(OBJS) $(LIB_PATH) -o $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c includes/minishell.h
	@mkdir -p $(OBJS_PATH)
	@$(CC) $(CFLAGS) -I $(INCS_PATH) -c $< -o $@

clean:
	@rm -rf $(OBJS_PATH)
	@make fclean -C ./libft/

fclean: clean
	@rm -f $(NAME)
	@rm /sgoinfre/goinfre/Perso/lfalkau/gdd.sh

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

move_script:
	@cp srcs/gdd.sh /sgoinfre/goinfre/Perso/lfalkau/gdd.sh
