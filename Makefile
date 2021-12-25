# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sanghunka <sanghunka@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/05 14:03:30 by sankang           #+#    #+#              #
#    Updated: 2021/12/25 19:48:22 by sanghunka        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = main
SRC = main.c get_next_line.c get_next_line_utils.c				
OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror


.PHONY: all bonus clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $^ -o $@

*.o: *.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

a:
	@gcc -D BUFFER_SIZE=10 get_next_line.c get_next_line_utils.c main.c

g:
	@gcc -D BUFFER_SIZE=10 -Wall -Wextra -Werror -g3 -fsanitize=address get_next_line.c get_next_line_utils.c main.c

run:
	@gcc -D BUFFER_SIZE=10 get_next_line.c get_next_line_utils.c main.c
	@#gcc -D BUFFER_SIZE=10 -Wall -Wextra -Werror get_next_line.c get_next_line_utils.c main.c
	@./a.out

rung:
	@gcc -D BUFFER_SIZE=10 -Wall -Wextra -Werror -g3 -fsanitize=address get_next_line.c get_next_line_utils.c main.c
	@./a.out