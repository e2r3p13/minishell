# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/12 15:15:55 by lfalkau           #+#    #+#              #
#    Updated: 2020/01/16 16:32:49 by lfalkau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCS_PATH = ./includes/
SRCS_PATH = ./srcs/
OBJS_PATH = ./objs/
LIBFT_A = ./libft/libft.a
LIBFT_M = ./libft/

SRCS = main.c

TMP = $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJS_PATH),$(TMP))

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror
OFLAGS = -g3 -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	@make -C $(LIBFT_M)
	@$(CC) $(CFLAGS) -I $(INCS_PATH) $(OBJS) $(LIBFT_A) -o $(NAME)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c includes/minishell.h
	@mkdir -p $(OBJS_PATH)
	@$(CC) $(CFLAGS) -I $(INCS_PATH) -c $< -o $@

bccyv: re clean

clean:
	@rm -rf $(OBJS_PATH)
	@make fclean -C ./libft/


fclean: clean
	@rm -rf $(NAME)

re: fclean all
