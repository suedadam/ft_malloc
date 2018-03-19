#!/usr/bin/make -f

################################################################################
# SETTINGS                                                                     #
################################################################################

NAME = libftprintf.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra
LIBFT = libft/libft.a
PRINTF_SRC = \
	ft_printf \
	integer \
	length \
	num_fetch \
	parse \
	special \
	strings \
	tools \
	utils \
	buffer \
	flags \
	special \
	wide \
	format

PRINTF_OBJ = $(patsubst %, obj/%.o, $(PRINTF_SRC))
INC = -I libft -I .

################################################################################
# COLORS                                                                       #
################################################################################

NC = \033[0m
GREEN = \033[1;32m
RED = \033[1;31m
YELLOW = \033[1;33m
BLUE = \033[1;36m

################################################################################
# RULES                                                                        #
################################################################################

all: $(NAME)

$(NAME): $(LIBFT) $(PRINTF_OBJ)
	@printf "$(YELLOW)%-50s$(NC)" "Building $@... "
	@ar rcs $(NAME) $(PRINTF_OBJ)
	@echo "$(GREEN)DONE$(NC)"

obj/%.o: %.c
	@mkdir -p $(dir $@)
	@echo " > Compiling $<..."
	@$(CC) $(OBJFLAGS) $(INC) -c $< -o $@

$(LIBFT):
	@printf "$(YELLOW)%-50s$(NC)" "Building $@... "
	@make -C libft

clean:
	@rm -rf obj
	@make -C libft clean
	@echo "$(RED)Object files removed$(NC)"

fclean: clean
	@rm -f $(PRINTF_OBJ)
	@make -C libft fclean
	@rm -f $(NAME)
	@echo "$(BLUE) $(NAME) removed$(NC)"

re: fclean all