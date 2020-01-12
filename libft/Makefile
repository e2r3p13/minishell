# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 11:56:25 by lfalkau           #+#    #+#              #
#    Updated: 2020/01/12 15:30:35 by lfalkau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INC_PATH = ./includes/
OBJ_PATH = ./obj/
SRC_PATH = ./src/

SRCS =			ft_atoi.c \
				ft_bzero.c \
				ft_isalnum.c \
				ft_isalpha.c \
				ft_isascii.c \
				ft_isdigit.c \
				ft_isprint.c \
				ft_isinset.c \
				ft_memcpy.c \
				ft_memccpy.c \
				ft_memmove.c \
				ft_memset.c \
				ft_memalloc.c \
				ft_tolower.c \
				ft_toupper.c \
				ft_strlen.c \
				ft_memchr.c \
				ft_memcmp.c \
				ft_strchr.c \
				ft_strrchr.c \
				ft_strncmp.c \
				ft_strnstr.c \
				ft_strdup.c \
				ft_strlcat.c \
				ft_strlcpy.c \
				ft_putstr_fd.c  \
				ft_putchar_fd.c \
				ft_putendl_fd.c \
				ft_putnbr_fd.c \
				ft_putstr.c  \
				ft_putchar.c \
				ft_putendl.c \
				ft_putnbr.c \
				ft_itoa.c \
				ft_substr.c \
				ft_strjoin.c \
				ft_strtrim.c \
				ft_calloc.c \
				ft_strmapi.c \
				ft_split.c \
				ft_lst_new.c \
 				ft_lst_addfront.c \
				ft_lst_size.c \
				ft_lst_last.c \
				ft_lst_iter.c \
				ft_lst_map.c \
				ft_lst_clear.c \
				ft_lst_delone.c \
				ft_lst_addback.c \
				ft_bit_itoc.c \
				ft_bit_ctoi.c \
				ft_bit_cctwo.c \
				ft_pow.c \
				ft_strcjoin.c \
				ft_realloc.c \
				get_next_line.c \
				ft_remove_spaces.c \
				ft_isstrdigit.c \
				ft_isrgb.c \
				ft_free_array.c \
				ft_color_from_rgb.c \

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

OBJ = $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJ_PATH),$(OBJ))

all: $(NAME)

$(NAME): $(OBJS) aff_e
	@ar rc $@ $(OBJS)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c includes/libft.h
	@printf "▬"
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) -I$(INC_PATH) -c $< -o $@

aff_e:
	@printf "\033[32m"
	@printf " [Done]"
	@printf "\033[0m"
	@printf "\n"

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)

re: fclean all
