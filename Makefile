NAME= Gomoku

CC= g++
CFLAGS= -std=c++11 -Wall -Werror -Wextra -g3 #-fsanitize=address
SRC_NAME= main.cpp \
          utils.cpp \
          gomoku.cpp \
          rules.cpp \
          defaultRules.cpp \
          player.cpp \
          randomPlayer.cpp
SRC_PATH= ./sources/
INC_PATH= ./includes/
OBJ_NAME= $(SRC_NAME:.cpp=.o)
OBJ_PATH= ./obj/
SRC= $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ= $(addprefix $(OBJ_PATH), $(OBJ_NAME))

.PHONY: all
all: $(NAME) end
	
end:
	@printf "\n$(NAME) successfully created\n"

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) -I$(INC_PATH) $(OBJ)
	@printf "\033[2K[ \033[31mcompiling\033[0m ] $< \r"

$(OBJ_PATH)%.o: $(SRC_PATH)%.cpp
	@mkdir $(OBJ_PATH) 2> /dev/null || echo "" > /dev/null
	@$(CC) -I$(INC_PATH) $(CFLAGS) -o $@ -c $<
	@printf " \033[2K[ \033[31mcompiling\033[0m ] $< \r"

.PHONY: clean
clean:
	@rm -f $(OBJ)
	@printf "[ \033[36mdelete\033[0m ] objects from $(NAME)\n"
	@rm -rf $(OBJ_PATH)

.PHONY: fclean
fclean: clean
	@printf "[ \033[36mdelete\033[0m ] $(NAME)\n"
	@rm -f $(NAME)

.PHONY: re
re: fclean all
