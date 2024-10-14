NAME    := parser
CFLAGS  := -Wextra -Wall -Werror
CC      = cc
INC     = -I includes -I includes/libft

LIBFT   = includes/libft

VPATH   =	src

SRC  := pa_main.c \
		pa_tokenizer.c

OBJS    := $(patsubst %.c, obj/%.o, $(SRC))

all: $(NAME)

# Build libft library
$(LIBFT)/libft.a:
	@make -C $(LIBFT)

$(NAME): $(OBJS) $(LIBFT)/libft.a
	@$(CC) $(CFLAGS) $(INC) -o $(NAME) $(OBJS) $(LIBFT)/libft.a
	@echo MAKING parser...

obj/%.o: %.c
	@mkdir -p obj
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	@rm -rf obj
	@make -C $(LIBFT) clean
	@echo MAKING clean...

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT) fclean
	@echo MAKING fclean...

re: fclean all

.PHONY: all clean fclean re bonus
