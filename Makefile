#!/usr/bin/make -f

################################################################################
# SETTINGS                                                                     #
################################################################################

MALLOC = libft_malloc_${HOSTTYPE}.so
CC = gcc
OBJFLAGS = -Wall -Werror -Wextra -c -fPIC
LIBFLAGS = -shared
LIBFT = libft/libft.a
SOURCE_DIR = src
MALLOC_SRC = \
	free \
	malloc \
	page_size \
	realloc \
	utils

MALLOC_OBJ = $(patsubst %, obj/%.o, $(MALLOC_SRC))
INC = -I libft
MALLOC_INC = -I includes

################################################################################
# COLORS                                                                       #
################################################################################

NC = \033[0m
GREEN = \033[1;32m
RED = \033[1;31m
YELLOW = \033[1;33m

################################################################################
# RULES                                                                        #
################################################################################

all: $(MALLOC)

$(MALLOC): $(LIBFT) $(MALLOC_OBJ)
	@printf "$(YELLOW)%-50s$(NC)" "Building $@... "
	@$(CC) $(LIBFLAGS) $(MALLOC_OBJ) -o $@
	@ln -s $@ libft_malloc.so
	@echo "$(GREEN)DONE$(NC)"

obj/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo " > Compiling $<..."
	@$(CC) $(OBJFLAGS) $(MALLOC_INC) -c $< -o $@

$(LIBFT):
	@printf "$(YELLOW)%-50s$(NC)" "Building $@... "
	@make -C libft

clean:
	@rm -rf obj
	@make -C libft clean
	@echo "$(RED)Object files removed$(NC)"

fclean: clean
	@make -C libft fclean
	@rm -f $(MALLOC)
	@rm -f libft_malloc.so
	@echo "$(MALLOC) removed$(NC)"

re: fclean all