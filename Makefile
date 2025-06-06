# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nass <nass@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/05 10:53:23 by nyousfi           #+#    #+#              #
#    Updated: 2025/06/06 23:27:41 by nass             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP
SRCS = src/main.c \
		src/parsing/loop.c \
		src/parsing/input.c \
		src/parsing/utils.c \
		src/parsing/error_checker/error_checker.c \
		src/parsing/lexer/lexer.c \
		src/parsing/lexer/extract.c \
		src/parsing/lexer/extract_utils.c \
		src/parsing/lexer/token.c \
		src/parsing/parser/parser.c \
		src/parsing/expand/expand.c \
		src/parsing/expand/expand_utils.c
		
MAKEDIR = make
OBJDIR = make/objs
SUBOBJDIR = make/objs/parsing \
			make/objs/exec \
			make/objs/parsing/error_checker \
			make/objs/parsing/lexer \
			make/objs/parsing/parser \
			make/objs/parsing/expand
DEPDIR = make/deps
SUBDEPDIR = make/deps/parsing \
			make/deps/exec \
			make/deps/parsing/error_checker \
			make/deps/parsing/lexer \
			make/deps/parsing/parser \
			make/deps/parsing/expand 

OBJS = $(SRCS:src/%.c=$(OBJDIR)/%.o)
DEPS = $(SRCS:src/%.c=$(DEPDIR)/%.d)

HEADER =	include/minishell.h \
			include/parsing/parsing.h \
			include/exec/exec.h

COMPILED = 0
MESSAGE_COLOR_GREEN = \033[1;32m
MESSAGE_COLOR_BLUE = \033[1;34m
MESSAGE_COLOR_YELLOW = \033[1;33m
MESSAGE_COLOR_RED = \033[1;31m
MESSAGE_RESET = \033[1;0m

all: $(NAME)
	@if [ $(COMPILED) -eq 1 ]; then \
		echo "$(MESSAGE_COLOR_BLUE)compilation done 🎉$(MESSAGE_RESET)"; \
	else \
		echo "$(MESSAGE_COLOR_BLUE)everything is already up to date 😉$(MESSAGE_RESET)"; \
	fi
	
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -lreadline -o $(NAME)
	@$(eval COMPILED := 1)

$(OBJDIR)/%.o: src/%.c $(HEADER)
	@echo "$(MESSAGE_COLOR_YELLOW)Compiling $@... 🛠️$(MESSAGE_RESET)"
	@mkdir -p $(OBJDIR) $(DEPDIR) $(SUBOBJDIR) $(SUBDEPDIR)
	@$(CC) $(CFLAGS) -Iinclude -Iinclude/parsing -Iinclude/exec -c $< -o $@
	@mv -f $(OBJDIR)/$*.d $(DEPDIR)/$*.d
	@$(eval COMPILED := 1)
	@echo "$(MESSAGE_COLOR_GREEN)Compilation of $@ done! ✅$(MESSAGE_RESET)"

-include $(DEPS)

clean:
	@if [ -d $(MAKEDIR) ] || [ -f $(NAME) ]; then \
		rm -rf $(MAKEDIR); \
		echo "$(MESSAGE_COLOR_RED)all files are deleted 🗑️$(MESSAGE_RESET)"; \
	else \
		echo "$(MESSAGE_COLOR_GREEN)files already deleted 😉$(MESSAGE_RESET)"; \
	fi


fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all files clean fclean re