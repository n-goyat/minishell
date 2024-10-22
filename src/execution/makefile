NAME    := shell
CFLAGS  := -Wextra -Wall -Werror
CC      = cc
INC     = -I includes -I includes/libft
LIBFT   = includes/libft
VPATH   = src
LDFLAGS := -lreadline

SRC  := main.c built-in.c ft_execute_command.c ft_execute_pipeline.c \
        ft_execute_builtin.c ft_handle_redirection.c ft_handle_signals.c \
        ft_wait_for_processes.c gestion_environment.c utils_fonction.c \
        gc.c pa_commands.c pa_env_expander.c pa_tokenizer.c pa_main.c

OBJS    := $(patsubst %.c, obj/%.o, $(SRC))

all: $(NAME)

# Build libft library
$(LIBFT)/libft.a:
	@make -C $(LIBFT)

$(NAME): $(OBJS) $(LIBFT)/libft.a
	@$(CC) $(CFLAGS) $(INC) -o $(NAME) $(OBJS) $(LIBFT)/libft.a $(LDFLAGS)
	@echo MAKING minishell execution process...

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

.PHONY: all clean fclean re
