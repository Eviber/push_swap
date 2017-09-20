# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/20 18:17:31 by ygaude            #+#    #+#              #
#    Updated: 2017/09/20 23:31:29 by ygaude           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = checker
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = checker_src/
LIBFT_DIR = libft/
OBJ_DIR = obj/

SRC = checker.c

OBJ = ${SRC:c=o}

all: $(NAME)

%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I libft/ -I include/ -c -o $(OBJ_DIR)$@ $^

$(NAME): $(OBJ)
	@make -C libft/
	@echo "Making checker..."
	@$(CC) $(CFLAGS) $(OBJ_DIR)$(OBJ) $(LIBFT_DIR)libft.a -I libft/ -I include/ -o $(NAME)
	@echo "Done !"

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "Object files removed."

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(NAME)
	@echo "$(NAME) removed"

re: fclean all
