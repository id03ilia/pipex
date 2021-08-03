NAME = pipex

NAME_B = pipex_b

HEADER = pipex.h

FLAGS = -Wall -Wextra -Werror

SRC = pipex.c ft_split.c ft_strlen.c ft_substr.c ft_putstr.c get_path.c free_mas.c ft_strjoin.c

SRC_B = pipex_bonus.c pipex_bonus2.c ft_split.c ft_strlen.c ft_substr.c ft_putstr.c get_path.c free_mas.c ft_strjoin.c

OBJ = $(SRC:.c=.o)

OBJ_B = $(SRC_B:.c=.o)

all: $(NAME)

bonus: $(NAME_B)

$(NAME): $(OBJ) $(HEADER)
	gcc -o $(NAME) $(FLAGS) $(OBJ)

$(NAME_B): $(OBJ_B) $(HEADER)
	gcc -o $(NAME_B) $(FLAGS) $(OBJ_B)

%.o:%.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(OBJ_B)

fclean: clean
	rm -f $(NAME)
	rm -f $(NAME_B)

re: fclean bonus all

.PHONY: all clean fclean bonus re
