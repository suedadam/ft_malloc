#!/usr/bin/make -f

################################################################################
# SETTINGS                                                                     #
################################################################################

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

MALLOC = libft_malloc_${HOSTTYPE}.so
CC = gcc
OBJFLAGS = -g -Wall -Werror -Wextra -c -fPIC
LIBFLAGS = -g -shared -ldl
LIBFT = deps/ft_printf/libft/libft.a
LIBPRINTF = deps/ft_printf/libftprintf.a
SOURCE_DIR = src
MALLOC_SRC = \
	free \
	malloc \
	page_size \
	realloc \
	utils \
	show_alloc \
	alloc_large \
	large_free \
	chksum

MALLOC_OBJ = $(patsubst %, obj/%.o, $(MALLOC_SRC))
INC = -I deps/ft_printf
MALLOC_INC = -I includes

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

all: $(MALLOC)

$(MALLOC): $(LIBPRINTF) $(MALLOC_OBJ)
	@printf "$(YELLOW)%-50s$(NC)" "Building $@... "
	@$(CC) $(LIBFLAGS) $(LIBPRINTF) $(LIBFT) $(MALLOC_OBJ) -o $@
	@rm -f libft_malloc.so
	@ln -s $@ libft_malloc.so
	@echo "$(GREEN)DONE$(NC)"

obj/%.o: $(SOURCE_DIR)/%.c
	@mkdir -p $(dir $@)
	@echo " > Compiling $<..."
	@$(CC) $(OBJFLAGS) $(INC) $(MALLOC_INC) -c $< -o $@

$(LIBPRINTF):
	@echo "Attempting"
	@printf "$(YELLOW)%-50s$(NC)" "Building $@... "
	@make -C deps/ft_printf

clean:
	@rm -rf obj
	@make -C deps/ft_printf clean
	@echo "$(RED)Object files removed$(NC)"

fclean: clean
	@make -C deps/ft_printf fclean
	@rm -f $(MALLOC)
	@rm -f libft_malloc.so
	@echo "$(BLUE) $(MALLOC) removed$(NC)"

re: fclean all