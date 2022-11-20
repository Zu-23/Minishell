SRC= utils/ft_isspace.c \
utils/ft_strdup.c \
utils/ft_strlen.c \
utils/ft_strtok.c \
utils/ft_substr.c \
utils/lst_utils.c \
utils/ft_strcmp.c \
main.c \

OBJ= $(SRC:.c=.o)
CFLAGS = gcc -Wall -Werror -Wextra 
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
