# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfalkau <lfalkau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 11:56:25 by lfalkau           #+#    #+#              #
#    Updated: 2020/04/10 15:39:16 by lfalkau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INCS_PATH = ./includes/
SRCS_PATH = ./srcs/
OBJS_PATH = ./objs/

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
				ft_strcmp.c \
				ft_strnstr.c \
				ft_strdup.c \
				ft_strndup.c \
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
				ft_strpush.c \
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
				dynstr_new.c \
				dynstr_from_str.c \
				dynstr_push.c \
				dynstr_pop.c \
				dynstr_insert_at.c \
				dynstr_remove_at.c \
				dynstr_join.c \
				dynstr_realloc.c \
				dynstr_clear.c \
				dynstr_free.c \
				argvlen.c \
				open_file.c \
				open_reg_file.c \

CC = gcc
CFLAGS = -Wall -Wextra -Werror

TMP = $(SRCS:.c=.o)
OBJS = $(addprefix $(OBJS_PATH),$(TMP))

NAME = libft.a

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $@ $(OBJS)

$(OBJS_PATH)%.o: $(SRCS_PATH)%.c $(INCS_PATH)/libft.h
	@mkdir -p $(OBJS_PATH)
	$(CC) $(CFLAGS) -I$(INCS_PATH) -c $< -o $@

clean:
	@rm -rf $(OBJS_PATH)

fclean: clean
	@rm -f $(NAME)

re: fclean all
