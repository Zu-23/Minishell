SRC= utils/ft_isspace.c \
utils/ft_strdup.c \
utils/ft_strlen.c \
utils/ft_strtok.c \
utils/ft_substr.c \
utils/lst_utils.c \
utils/lst_utils_two.c \
utils/ft_strcmp.c \
utils/lexer_analyzer.c \
utils/ft_perror.c \
utils/ft_split.c \
utils/ast.c \
main.c \

OBJ= $(SRC:.c=.o)
CFLAGS = gcc -Wall -Werror -Wextra -g
RLF= -lreadline
RM = rm -f
AR = ar rcs
NAME= minishell

all: $(NAME)

$(NAME): $(OBJ)
	$(CFLAGS) $(OBJ) $(RLF) -o $(NAME)

%.o: %.c
	$(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re
