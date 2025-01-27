# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: atazzit <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/25 15:18:26 by atazzit           #+#    #+#              #
#    Updated: 2025/01/25 15:18:27 by atazzit          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
CC = cc
NAME = pipex
CFLAGS = -Wall -Wextra -Werror -I./Includes/ -g3

RESET  = \033[0m
RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m
BOLD   = \033[1m

SRC = main.c \
      pipex.c 
OBJ = $(SRC:.c=.o)

LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) ready$(RESET)"

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

%.o: %.c pipex.h
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(YELLOW)✓ $<$(RESET)"

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(RED)✓ objects cleaned$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(RED)✓ executable removed$(RESET)"

re: fclean all

.PHONY: all clean fclean re
