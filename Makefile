# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ygaude <ygaude@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/09/20 18:17:31 by ygaude            #+#    #+#              #
#    Updated: 2018/02/19 23:34:39 by ygaude           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CHECKER = checker
PUSH_SWAP = push_swap
CC = gcc
CFLAGS = -g -Wall -Wextra -Werror `sdl2-config --cflags`
LFLAGS = `sdl2-config --libs`
SRC_DIR = src/
LIBFT_DIR = libft/
OBJ_DIR = obj/

CHKR_SRC = apply.c checker.c events.c parser.c visu.c visutools.c list.c       \
		   tools.c display.c
PS_SRC =	apply.c parser.c push_swap.c list.c quicksort.c smallsort.c tools.c

CHECKER_OBJ = ${CHKR_SRC:c=o}
PS_OBJ = ${PS_SRC:c=o}

all: $(CHECKER) $(PUSH_SWAP)

$(addprefix $(OBJ_DIR), %.o): $(SRC_DIR)%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -I libft/ -I include/ -c -o $@ $^

$(CHECKER): $(addprefix $(OBJ_DIR), $(CHECKER_OBJ))
	@make -C libft/
	@echo "Making checker..."
	@$(CC) $(addprefix $(OBJ_DIR), $(CHECKER_OBJ)) $(LIBFT_DIR)libft.a         \
								$(LFLAGS) -I libft/ -I include/ -o $(CHECKER)
	@echo "Done !"

$(PUSH_SWAP): $(addprefix $(OBJ_DIR), $(PS_OBJ))
	@make -C libft/
	@echo "Making push_swap..."
	@$(CC) $(addprefix $(OBJ_DIR), $(PS_OBJ)) $(LIBFT_DIR)libft.a    \
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
