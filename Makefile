# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/20 18:17:31 by ygaude            #+#    #+#              #
#    Updated: 2017/10/23 19:34:42 by ygaude           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CHECKER = checker
PUSH_SWAP = push_swap
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = src/
LIBFT_DIR = libft/
OBJ_DIR = obj/

CHECKER_SRC =	apply.c checker.c parser.c
PS_SRC =	apply.c parser.c push_swap.c list.c

CHECKER_OBJ = ${CHECKER_SRC:c=o}
PS_OBJ = ${PS_SRC:c=o}

all: $(CHECKER) $(PUSH_SWAP)

%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I libft/ -I include/ -c -o $(OBJ_DIR)$@ $^

$(CHECKER): $(CHECKER_OBJ)
	@make -C libft/
	@echo "Making checker..."
	@$(CC) $(CFLAGS) $(addprefix $(OBJ_DIR), $(CHECKER_OBJ))                   \
					 $(LIBFT_DIR)libft.a -I libft/ -I include/ -o $(CHECKER)
	@echo "Done !"

$(PUSH_SWAP): $(PS_OBJ)
	@make -C libft/
	@echo "Making push_swap..."
	@$(CC) $(CFLAGS) $(addprefix $(OBJ_DIR), $(PS_OBJ)) $(LIBFT_DIR)libft.a    \
		-I libft/ -I include/ -o $(PUSH_SWAP)
	@echo "Done !"

clean:
	@make -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)
	@echo "Object files removed."

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -f $(CHECKER)
	@echo "$(CHECKER) removed"
	@rm -f $(PUSH_SWAP)
	@echo "$(PUSH_SWAP) removed"

re: fclean all
