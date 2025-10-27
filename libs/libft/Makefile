# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: macarval <macarval@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/21 00:40:38 by macarval          #+#    #+#              #
#    Updated: 2024/10/30 17:05:54 by macarval         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

SRCS		= ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c			\
			ft_isprint.c													\
			\
			ft_atoi.c ft_itoa.c ft_tolower.c ft_toupper.c					\
			\
			ft_lstadd_back.c ft_lstadd_front.c ft_lstclear.c				\
			ft_lstdelone.c ft_lstiter.c ft_lstlast.c ft_lstmap.c			\
			ft_lstnew.c ft_lstsize.c										\
			\
			ft_bzero.c ft_calloc.c ft_memchr.c ft_memcmp.c ft_memcpy.c		\
			ft_memmove.c ft_memset.c										\
			\
			ft_split.c ft_strdup.c ft_strjoin.c ft_strlcpy.c				\
			ft_strmapi.c ft_strnstr.c ft_strtrim.c ft_strchr.c				\
			ft_striteri.c ft_strlcat.c ft_strlen.c ft_strncmp.c				\
			ft_strrchr.c ft_substr.c										\
			\
			free_split.c													\
			\
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c					\
			ft_putnbr_fd.c													\
			\
			get_next_line.c get_next_line_utils.c							\
			\
			ft_printf.c ft_format.c ft_printf_control.c ft_printf_utils.c

VPATH		= srcs/ srcs/checkers srcs/conversors srcs/list srcs/memory		\
			srcs/string srcs/utils srcs/writers srcs/gnl srcs/ft_printf

OBJS_PATH	= obj

INCLUDE		=-I./includes

FLAGS		= -Wall -Wextra -Werror -g3
CC			= gcc

#colors
GREEN		= \033[0;32m
YELLOW		= \033[0;33m
BLUE		= \033[0;34m
MAGENTA		= \033[0;35m
CYAN		= \033[0;36m
RESET		= \033[0m

OBJS 		= $(addprefix ${OBJS_PATH}/, ${SRCS:.c=.o})

all: $(NAME)

$(NAME):	$(OBJS_PATH) $(OBJS)
			@ar -rcs $(NAME) $(OBJS)
			@echo "\n$(CYAN)$(NAME): $(GREEN)Done!$(RESET)\n"

$(OBJS_PATH):
			@mkdir -p $(OBJS_PATH)

$(OBJS_PATH)/%.o: %.c
			@$(CC) $(FLAGS) $(INCLUDE) -c $< -o $@
# 			@echo -n "$(YELLOW)Generating $(CYAN)$(NAME) $(YELLOW)objects..." $@
# 			@echo -n "\n"

clean:
			@rm -fr $(OBJS_PATH)
			@echo "$(CYAN)$(NAME): $(GREEN)Clean done!$(RESET)"

fclean:		clean
			@rm -fr ${NAME}
			@echo "$(CYAN)$(NAME): $(GREEN)Full clean done!$(RESET)"

re:			fclean all

.PHONY: all clean fclean re
