NAME    := shell
CFLAGS  := -Wextra -Wall -Werror -fsanitize=address
CC      = cc
INC     = -I includes -I includes/libft -I src/parser/includes -I src/execution/includes
LIBFT   = includes/libft
VPATH   = src/parser src/execution  # Now pointing directly to parser and execution

LDFLAGS := -lreadline


DEF_COLOR = \033[0;39m
GRAY      = \033[0;90m
RED       = \033[0;91m
GREEN     = \033[0;92m
YELLOW    = \033[0;93m
BLUE      = \033[0;94m
MAGENTA   = \033[0;95m
CYAN      = \033[0;96m
WHITE     = \033[0;97m

# Updated SRC to directly reference the files in parser and execution
SRC  := parser/main.c\
        execution/built-in.c\
        execution/ft_execute_builtin.c\
        execution/ft_execute_command.c\
        execution/ft_execute_pipeline.c\
        execution/ft_execute_pipeline_bis.c\
        execution/ft_handle_redirection.c\
        execution/ft_handle_signal.c\
        execution/ft_here_doc.c\
        execution/ft_wait_for_processes.c\
        execution/gc.c\
        execution/gestion_environment.c\
        execution/utils_fonction.c\
		execution/builtin_export.c\
        parser/debug.c\
        parser/pa_commands.c\
        parser/pa_env_expander_utils.c\
        parser/pa_env_expander.c\
        parser/pa_free_2.c\
        parser/pa_free.c\
        parser/pa_init.c\
        parser/pa_tokenizer_utils_2.c\
        parser/pa_tokenizer_utils.c\
        parser/pa_tokenizer.c\
        parser/pa_utils_add.c\
        parser/pa_utils_create_2.c\
        parser/pa_utils_create.c\

# Object file paths
OBJS    := $(patsubst src/%.c, obj/%.o, $(SRC))

all: $(NAME)

# Build libft library
$(LIBFT)/libft.a:
	@make -C $(LIBFT)

$(NAME): $(OBJS) $(LIBFT)/libft.a
	@$(CC) $(CFLAGS) $(INC) -o $(NAME) $(OBJS) $(LIBFT)/libft.a $(LDFLAGS)
	@echo "$(GREEN)MAKING minishell execution process..."

obj/%.o: src/%.c
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
