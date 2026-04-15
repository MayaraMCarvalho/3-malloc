# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 16:33:22 by macarval          #+#    #+#              #
#    Updated: 2026/04/14 21:35:45 by macarval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Project Configuration ---
SYMLINK		= libft_malloc.so

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		= obj/libft_malloc_$(HOSTTYPE).so

# --- Sources and Objects ---
SRCS		= free.c malloc.c realloc.c show_alloc_mem_ex.c show_alloc_mem.c \
			block.c find_block.c large_block.c utils.c zone.c

VPATH		= srcs/:srcs/utils/
OBJS_PATH	= obj
OBJS 		= $(addprefix $(OBJS_PATH)/, $(SRCS:.c=.o))
HEADERS		= include/malloc.h srcs/utils/utils_malloc.h srcs/utils/colors.h

# --- Libft Configuration ---
LIBFT_PATH	= libft
LIBFT_INC	= $(LIBFT_PATH)/includes
LIBFT		= $(LIBFT_PATH)/libft.a
INCLUDE		= -I./include -I$(LIBFT_INC) -I./srcs/utils

# --- Compiler and Flags ---
CC			= gcc
CFLAGS		= -g3 -Wall -Wextra -Werror -fPIC -fvisibility=hidden
LDFLAGS		= -L. -lft_malloc -Wl,-rpath,$(shell pwd)

# --- Test Program Configuration ---
COMP_PATH	= test
COMP_SRCS	= $(COMP_PATH)/info.c $(COMP_PATH)/test_malloc.c
COMP		= $(OBJS_PATH)/test_malloc

# Regular colors
RED			= \033[0;31m
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
BLUE		= \033[0;34m
PURPLE		= \033[0;35m
CYAN		= \033[0;36m
WHITE		= \033[0;37m
RESET		= \033[0m

# Bold
BRED		= \033[1;31m
BGREEN		= \033[1;32m
BYELLOW		= \033[1;33m
BBLUE		= \033[1;34m
BPURPLE		= \033[1;35m
BCYAN		= \033[1;36m
BWHITE		= \033[1;37m


# --- Rules ---

all: 		$(NAME)

$(NAME):	$(LIBFT) $(OBJS)

			@echo "\n$(YELLOW)Creating dynamic library $(NAME)...$(RESET)"
			@$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJS) $(LIBFT)

			@echo "$(YELLOW)Creating a symbolic link $(SYMLINK)...$(RESET)"
			@ln -sf $(NAME) $(SYMLINK)
			@echo "$(GREEN)Library $(NAME) and link $(SYMLINK) created!$(RESET)"

$(LIBFT):
			@$(MAKE) -sC $(LIBFT_PATH)

$(OBJS_PATH):
			clear
			@mkdir -p $(OBJS_PATH)

$(OBJS_PATH)/%.o: %.c $(HEADERS) | $(OBJS_PATH)
			@echo -n "$(YELLOW)Compiling $<...$(RESET)"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
			@echo " $(GREEN)✔$(RESET)"

# --- Clean Rules ---
clean:
			@$(MAKE) -sC $(LIBFT_PATH) fclean
			@rm -rf $(OBJS_PATH)
			@echo "$(CYAN)malloc: $(GREEN)Clean object directory!$(RESET)"

fclean:		clean
			@rm -f $(NAME) $(SYMLINK) $(COMP)
			@echo "$(CYAN)malloc: $(GREEN)Complete cleaning!$(RESET)"

re:			fclean all

# --- Compile Rules ---
$(COMP):	$(COMP_SRCS) $(NAME) | $(OBJS_PATH)
			@echo "$(YELLOW)Compiling test program $(COMP)...$(RESET)"
			@$(CC) $(CFLAGS) $(INCLUDE) $(COMP_SRCS) $(LIBFT) $(LDFLAGS) -o $(COMP)

comp:		$(NAME) $(COMP)

run:		comp
			clear
			@echo "$(CYAN)Executing $(COMP) with $(SYMLINK)...$(RESET)"
			@LD_PRELOAD=./$(SYMLINK) ./$(COMP) || true
			@echo "$(CYAN)Execution complete.$(RESET)"

test:		comp
			@echo "$(CYAN)Running tests...$(RESET)"
			@./$(COMP_PATH)/tests.sh

git:
			clear
			@$(MAKE) --no-print-directory fclean
			@git add .
			@git status
			@echo "$(BPURPLE)Choose the commit type:"; \
			echo "$(BYELLOW)1. feat: $(WHITE)Adds a new feature to your codebase"; \
			echo "$(BYELLOW)2. fix: $(WHITE)Solves a problem in your codebase"; \
			echo "$(BYELLOW)3. docs: $(WHITE)Documentation changes"; \
			echo "$(BYELLOW)4. style: $(WHITE)Formatting, spacing, etc."; \
			echo "$(BYELLOW)5. refactor: $(WHITE)Refactoring code used in production, e.g. renaming a variable"; \
			echo "$(BYELLOW)6. test: $(WHITE)Adding tests, refactoring tests"; \
			echo "$(BYELLOW)7. chore: $(WHITE)Adjust build script, updating dependencies, makefile etc"; \
			read type_choice; \
			case $$type_choice in \
						1) type="feat" ;; \
						2) type="fix" ;; \
						3) type="docs" ;; \
						4) type="style" ;; \
						5) type="refactor" ;; \
						6) type="test" ;; \
						7) type="chore" ;; \
						*) echo "$(BRED)Invalid choice"; exit 1 ;; \
			esac; \
			echo -n "\n"; \
			echo "$(GREEN)Enter the commit message:"; \
			read msg; \
			echo -n "\n"; \
			echo "$(BLUE)"; \
			git commit -m "[malloc] $$type: $$msg"; \
			git push

help:
			@echo "$(CYAN)Available targets:$(RESET)"
			@echo "  $(BGREEN)all$(RESET) - Build the library"
			@echo "  $(BGREEN)re$(RESET) - Rebuild the library (clean + all)"
			@echo "  $(BGREEN)clean$(RESET) - Remove object files"
			@echo "  $(BGREEN)fclean$(RESET) - Remove object files and library"
			@echo "  $(BGREEN)comp$(RESET) - Compile test program"
			@echo "  $(BGREEN)run$(RESET) - Run test program with the library"
			@echo "  $(BGREEN)test$(RESET) - Run all tests"
			@echo "  $(BGREEN)git$(RESET) - Add, commit, and push changes to git"
			@echo "  $(BGREEN)help$(RESET) - Show this help message"

.PHONY:		all re clean fclean comp run test git
