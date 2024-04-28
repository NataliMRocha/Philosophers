NAME = philo
CC =  gcc -lpthread -pthread
FLAGS = -Wall -Wextra -Werror
DFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=thread
BIN = ./bin/
HEADERS = -I /philosophers.h -I ./libft
LIB = ./libft/libft.a
SRCS = $(addprefix ./src/, main.c utils.c init.c dinner.c check_threads.c get_set.c monitor.c mutex_and_thread_handle.c validate_and_parse.c)
OBJS = $(patsubst ./src/%.c, $(BIN)%.o, $(SRCS))

ifdef WITH_DEBBUG
	FLAGS = $(DFLAGS)
endif

define debug
	$(call clean)
	$(call fclean)
	$(MAKE) WITH_DEBBUG=TRUE -s
endef

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

debug:
	$(call debug)

re: fclean all

.PHONY: all clean fclean re
