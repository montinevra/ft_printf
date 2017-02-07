# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pvan-erp <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/12/22 01:09:32 by pvan-erp          #+#    #+#              #
#    Updated: 2017/01/17 22:07:10 by pvan-erp         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRC = ft_printf.c get_specifier.c print_int.c print_str.c padding.c
OBJ = $(SRC:.c=.o)

.PHONY: all clean fclean re test asan
	

all: $(NAME)
	

$(NAME): $(SRC) $(LSRC) libft/libft.a
	$(CC) -c $(SRC) $(CFLAGS)
	cp libft/libft.a $(NAME)
	ar r $(NAME) $(OBJ)

libft/libft.a:
	make -C ./libft
	
clean:
	rm -f $(OBJ)
	make -C libft/ clean

fclean: clean
	rm -f $(NAME)
	make -C libft/ fclean

re: fclean all


test: all main.c
	$(CC) main.c -L. -lftprintf
	./a.out

asan: all main.c
	$(CC) main.c -L. -lftprintf -fsanitize=address
	./a.out
