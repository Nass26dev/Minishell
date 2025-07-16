# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nyousfi <nyousfi@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 13:53:26 by eelissal          #+#    #+#              #
#    Updated: 2025/07/03 15:47:41 by nyousfi          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
MAKEFLAGS += --no-print-directory
CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP -g3

SRC_DIR = src
INC_DIR = includes

MAKEDIR = make
OBJDIR = ../make/objs
SUBOBJDIR = ../make/objs/libft/gnl \
			../make/objs/libft/printf \

DEPDIR = ../make/deps
SUBDEPDIR = ../make/deps/libft/gnl \
			../make/deps/libft/printf \
			
SRCS =	ft_atoi.c \
		ft_bzero.c \
		ft_calloc.c \
		ft_isalnum.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_itoa.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_memset.c \
		ft_putchar_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c \
		ft_putstr_fd.c \
		ft_split.c \
		ft_strchr.c \
		ft_strdup.c \
		ft_strcdup.c \
		ft_striteri.c \
		ft_strjoin.c \
		ft_strlcat.c \
		ft_strlcpy.c \
		ft_strlen.c \
		ft_strmapi.c \
		ft_strcmp.c \
		ft_strncmp.c \
		ft_strnstr.c \
		ft_strrchr.c \
		ft_strtrim.c \
		ft_substr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_lstnew.c \
		ft_lstadd_front.c \
		ft_lstsize.c \
		ft_lstlast.c \
		ft_lstadd_back.c \
		ft_lstdelone.c \
		ft_lstclear.c \
		ft_lstiter.c \
		ft_lstmap.c \

HEADERS = $(INC_DIR)/libft.h

OBJS = $(SRCS:%.c=$(OBJDIR)/%.o)
DEPS = $(SRCS:%.c=$(DEPDIR)/%.d)

COMPILED = 0
MESSAGE_COLOR_GREEN = \033[1;32m
MESSAGE_COLOR_BLUE = \033[1;34m
MESSAGE_COLOR_YELLOW = \033[1;33m
MESSAGE_COLOR_RED = \033[1;31m
MESSAGE_RESET = \033[1;0m

all: $(NAME)
	@if [ $(COMPILED) -eq 1 ]; then \
		echo "$(MESSAGE_COLOR_BLUE)libft compiled 🎉$(MESSAGE_RESET)"; \
	else \
		echo "$(MESSAGE_COLOR_BLUE)libft already up to date 😉$(MESSAGE_RESET)"; \
	fi

$(OBJDIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@echo "$(MESSAGE_COLOR_YELLOW)Compiling $@... 🛠️$(MESSAGE_RESET)"
	
	@mkdir -p $(OBJDIR) $(DEPDIR) $(SUBOBJDIR) $(SUBDEPDIR)
	@$(CC) $(CFLAGS) -I$(INC_DIR) -c $< -o $@
	@mv -f $(OBJDIR)/$*.d $(DEPDIR)/$*.d
	@$(eval COMPILED := 1)
	@echo "$(MESSAGE_COLOR_GREEN)Compiled $@ ✅$(MESSAGE_RESET)"

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@$(eval COMPILED := 1)

-include $(DEPS)

clean:
	@if [ -d $(MAKEDIR) ] || [ -f $(NAME) ]; then \
		rm -rf $(MAKEDIR); \
	fi

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
