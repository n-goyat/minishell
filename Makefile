# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maba <maba@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/05 17:27:42 by maba              #+#    #+#              #
#    Updated: 2024/10/05 17:46:50 by maba             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= minishell

CFLAGS	:= -Wextra -Wall -Werror

HEADERS	:= -I ./include -I ./libft

SRCS	:= src/main.c

OBJS	:= ${SRCS:.c=.o}

all: $(NAME)

libft/libft.a:
	@make -C libft

%.o: src/%.c
	@$(CC) $(CFLAGS) $(HEADERS) -o $@ -c $< && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS) libft/libft.a
	@$(CC) $(OBJS) libft/libft.a -o $(NAME)

clean:
	@make -C libft clean
	@rm -rf $(OBJS)

fclean: clean
	@make -C libft fclean
	@rm -rf $(NAME)

re: clean all

.PHONY: all clean fclean re
