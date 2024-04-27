NAME = philosophers
CC =  gcc -pthread
FLAGS = -Wall -Wextra -Werror
BIN = ./bin/
HEADERS = -I /philosophers.h -I ./libft
LIB = ./libft/libft.a
SRCS = $(addprefix ./src/, main.c utils.c parsing.c init.c dinner.c)
OBJS = $(patsubst ./src/%.c, $(BIN)%.o, $(SRCS))

all: libft/libft.a $(BIN) $(NAME)

libft/libft.a:
	@make -sC ./libft 

$(BIN)%.o: ./src/%.c
	@$(CC) $(FLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)\n"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LIB) $(HEADERS) -o $(NAME)

$(BIN):
	@mkdir -p $(BIN)

clean:
	rm -rf $(BIN)
	@make clean -sC ./libft 

fclean: clean
	rm -rf $(NAME)
	rm -rf ./libft/libft.a

re: fclean all

.PHONY: all clean fclean re
