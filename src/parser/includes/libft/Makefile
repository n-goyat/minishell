# Compiler
CC := cc

# Compiler flags
CFLAGS := -Wall -Wextra -Werror

# Library name
NAME := libft.a

# Source files
SRCS := ft_atoi.c \
		ft_atod.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_strndup.c\
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_striteri.c \
		ft_lstadd_back_bonus.c \
		ft_lstadd_front_bonus.c \
		ft_lstclear_bonus.c \
		ft_lstdelone_bonus.c \
		ft_lstiter_bonus.c \
		ft_lstlast_bonus.c \
		ft_lstmap_bonus.c \
		ft_lstnew_bonus.c \
		ft_lstsize_bonus.c

# Object files
OBJS := $(SRCS:.c=.o)

# Build rule
all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $@ $^

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	@rm -f $(OBJS)

# Clean and remove library rule
fclean: clean
	@rm -f $(NAME)

# Rebuild rule
re: fclean all

.PHONY: all clean fclean re bonus


# SRCS: List of source files.
# OBJS: List of object files.
# LIBNAME: Name of the library.
# all: Default target (equivalent to make libft.a).
# $(LIBNAME): Rule to create the library.
# %.o: %.c: Rule for compiling individual source files.
# clean: Rule to remove object files.
# fclean: Rule to remove library and object files.
# re: Rule to rebuild everything.
# .PHONY: Marks targets as not representing files. So if you have a file name called "clean" or "all" doesn't get confusing
# Variables defined with := in GNU make are expanded when they are defined rather than when they are used.
# $< points to the first prerequisite.
# $@ points to the target
# $^ : all the prerequipments-dependencies
# ar -rcs: ar creates-modifies a group of files combined into an archive,s is like ranlib(), -c means be silent not print info, -r gives the archive file position
# % is pattern matching character ex. %.c %.o means if I have file1.c I should have same name file1.o
# ranlib command converts each Archive library to a random library. A random library is an archive library that contains a symbol table.
# to run makefile use "make -f name_of_file" or just make if name is the default Makefile or makefile
# := instead of = to avoid infinite recursion if ex. You type CC = $(CC)
#SRCS := $(wildcard *.c): $(wildcard pattern) is one of the functions for filenames. In this case, all files with the .c extension will be stored in a variable SRCS.
#BINS := $(SRCS:%.c=%): This is called as substitution reference. In this case, if SRCS has values 'foo.c bar.c', BINS will have 'foo bar'.