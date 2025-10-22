# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 16:33:22 by macarval          #+#    #+#              #
#    Updated: 2025/10/21 14:11:58 by macarval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# --- Project Configuration ---
SYMLINK		= libft_malloc.so

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		= $(OBJS_PATH)/libft_malloc_$(HOSTTYPE).so

# --- Sources and Objects ---
SRCS		= malloc.c free.c realloc.c show_alloc_mem.c utils.c

VPATH		= srcs/
OBJS_PATH	= obj
OBJS 		= $(addprefix $(OBJS_PATH)/, $(SRCS:.c=.o))

# --- Libft Configuration ---
LIBFT_PATH	= ./libs/libft
LIBFT_INC	= $(LIBFT_PATH)/includes
LIBFT		= $(LIBFT_PATH)/libft.a
INCLUDE		= -I./include -I$(LIBFT_INC)

# --- Compiler and Flags ---
CC			= gcc
CFLAGS		= -g3 -Wall -Wextra -Werror -fPIC
LDFLAGS		= -L. -lft_malloc

# --- Test Program Configuration ---
TEST_SRCS	= main.c
TEST		= $(OBJS_PATH)/test_malloc

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

$(NAME):	$(LIBFT) $(OBJS_PATH) $(OBJS)

			@echo "\n$(YELLOW)Creating dynamic library $(NAME)...$(RESET)"
			@$(CC) $(CFLAGS) -shared -o $(NAME) $(OBJS) $(LIBFT)

			@echo "$(YELLOW)Creating a symbolic link $(SYMLINK)...$(RESET)"
			@ln -sf $(NAME) $(SYMLINK)
			@echo "$(GREEN)Library $(NAME) and link $(SYMLINK) created!$(RESET)"

$(LIBFT):
			clear
			@make -sC $(LIBFT_PATH)

$(OBJS_PATH):
			@mkdir -p $(OBJS_PATH)

$(OBJS_PATH)/%.o: %.c
			@echo -n "$(YELLOW)Compiling $<...$(RESET)"
			@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@
			@echo " $(GREEN)✔$(RESET)"

# --- Clean Rules ---
clean:
			@make -sC $(LIBFT_PATH) fclean
			@rm -rf $(OBJS_PATH)
			@echo "$(CYAN)malloc: $(GREEN)Clean object directory!$(RESET)"

fclean:		clean
			@rm -f $(SYMLINK)
			@rm -f $(TEST)
			@echo "$(CYAN)malloc: $(GREEN)Complete cleaning!$(RESET)"

re:			fclean all

# --- Test Rules ---
$(TEST):	$(OBJS_PATH) $(TEST_SRCS)
			@echo "$(YELLOW)Compiling test program $(TEST)...$(RESET)"
			@$(CC) $(CFLAGS) $(INCLUDE) $(TEST_SRCS) -o $(TEST)

test:		re $(TEST)

run:		test
			@echo "$(CYAN)Executing $(TEST) with $(SYMLINK)...$(RESET)"
			@LD_PRELOAD=./$(SYMLINK) ./$(TEST) || true
			@echo "$(CYAN)Execution complete.$(RESET)"

git:
			clear
			@make --no-print-directory fclean
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

.PHONY:		all re clean fclean test run comp val git
