# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rsibiet <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/27 16:54:50 by rsibiet           #+#    #+#              #
#    Updated: 2017/05/15 10:37:34 by rsibiet          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME1 = ft_nm
NAME2 = ft_otool

FTC1 = 	main.c \
		nm_32.c \
		nm_cigam_32.c \
		nm_64.c \
		nm_cigam_64.c \
		section.c \
		print_res.c \
		lists.c \
		ft_swap.c \
		fat_arch.c

FTC2 = srcs/otool/main.c \
	   srcs/otool/otool.c \
	   srcs/otool/otool_cigam.c \
	   srcs/otool/print_res.c \
	   srcs/nm/ft_swap.c \
	   srcs/otool/fat_arch.c

SRC_FTC1 = $(addprefix srcs/nm/, $(FTC1))

FTO1 = $(SRC_FTC1:%.c=%.o)
FTO2 = $(FTC2:%.c=%.o)

EXEC = libft.a
.PHONY: all re clean fclean

all: $(EXEC) $(NAME1) $(NAME2)

$(EXEC):
	@echo "\033[34;1m____________________________ Loading libft _______________________________\033[0m\n"
	@make -C ./libft

$(NAME1): $(FTO1)
	@echo ""
	@echo "\033[32m• $(NAME1) created!\033[0m"
	@echo "\033[32m• $(NAME2) created!\033[0m"
	@echo "\n"
	@gcc -Wall -Wextra -Werror -o $(NAME1) $(FTO1) -I ./includes/ -L./libft -lft

$(NAME2): $(FTO2)
	@gcc -Wall -Wextra -Werror -o $(NAME2) $(FTO2) -I ./includes/ -L./libft -lft

%.o: %.c
	@tput civis
	@gcc -Wall -Wextra -Werror -I./libft/ -I./includes/ -o $@ -c $<
	@tput cnorm

clean:
	@rm -rf $(FTO1)
	@rm -rf $(FTO2)
	@echo "\033[33m• $(NAME1) & $(NAME2) object deleted!\033[0m"

fclean: clean
	@rm -rf $(NAME1)
	@rm -rf $(NAME2)
	@echo "\033[31;1m• \033[31m$(NAME1) & $(NAME2) deleted!\033[0m"

re: fclean all
