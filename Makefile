# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jcluzet <jo@cluzet.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/21 01:05:24 by jcluzet           #+#    #+#              #
#    Updated: 2021/07/01 00:32:32 by jcluzet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = Minishell

OBJ_PATH = srcs/*/*.o

SRC =				srcs/*/*.c

OBJ_NAME = $(SRC:.c=.o)

# Files

OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

# Flags

CC = gcc

CFLAGS = -g3 -fsanitize=address -lreadline

# CFLAGS =  -Wall -Werror -Wextra -g -fsanitize=address

# Rules

all:  $(NAME)

$(NAME) :	$(OBJ)
	@echo "\033[34mCompilation of $(NAME) ...\033[0m"
	@gcc -o $(NAME) $(CFLAGS) $(SRC)
	@echo "\033[32m$(NAME) created\n\033[0m"

clean:
	@echo "\033[33mRemoval of .o files of $(NAME)...\033[0m"
	@rm -f $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "\033[31mFiles .o deleted\n\033[0m"

fclean: clean
	@echo "\033[33mRemoval of $(NAME)...\033[0m"
	@rm -rf $(NAME) Minishell.dSYM
	@echo "\033[31mBinary $(NAME) deleted\n\033[0m"

re: fclean all

.PHONY: all, clean, fclean, re
