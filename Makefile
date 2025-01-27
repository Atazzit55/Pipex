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

# Color Definitions
RESET  = \033[0m
RED    = \033[31m
GREEN  = \033[32m
YELLOW = \033[33m
BLUE   = \033[34m
BOLD   = \033[1m

# Source and Object Files
SRC = main.c \
      pipex.c 
OBJ = $(SRC:.c=.o)

# Libft Configuration
LIBFT_DIR = ./libft
LIBFT = $(LIBFT_DIR)/libft.a

# Default Target
all: $(NAME)

# Link Executable
$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) -L$(LIBFT_DIR) -lft -o $(NAME)
	@echo "$(GREEN)✓ $(NAME) ready$(RESET)"

# Compile Libft
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory

# Compile Object Files
%.o: %.c pipex.h
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(YELLOW)✓ $<$(RESET)"

# Clean Object Files
clean:
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(RED)✓ objects cleaned$(RESET)"

# Full Clean
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(RED)✓ executable removed$(RESET)"

# Rebuild
re: fclean all

.PHONY: all clean fclean re
