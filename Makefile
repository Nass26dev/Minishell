# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/05 10:53:23 by nyousfi           #+#    #+#              #
#    Updated: 2025/06/06 15:25:27 by eelissal         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP
SRCS =	src/main.c \
		src/parsing/loop.c \
		src/parsing/error_checker/error_checker.c \
		src/parsing/lexer/lexer.c \
		src/parsing/parser/parser.c \
		src/parsing/line.c \
		src/exec/exec.c \
		src/exec/builtin/builtin.c \
		src/exec/exec_cmd/exec_cmd.c \
		src/exec/exec_redir/exec_redir.c \
		src/exec/exec_pipe/exec_pipe.c \
		src/exec/exec_operator/exec_operator.c \
		src/exec/exec_parenthesis/exec_parenthesis.c \
		src/exec/exec_separator/exec_separator.c \
		
MAKEDIR = make
OBJDIR = make/objs
SUBOBJDIR = make/objs/parsing \
			make/objs/exec \
			make/objs/parsing/error_checker \
			make/objs/parsing/lexer \
			make/objs/parsing/parser \
			make/objs/exec/builtin \
			make/objs/exec/exec_cmd \
			make/objs/exec/exec_redir \
			make/objs/exec/exec_pipe \
			make/objs/exec/exec_operator \
			make/objs/exec/exec_parenthesis \
			make/objs/exec/exec_separator \

DEPDIR = make/deps
SUBDEPDIR = make/deps/parsing \
			make/deps/exec \
			make/deps/parsing/error_checker \
			make/deps/parsing/lexer \
			make/deps/parsing/parser \
			make/deps/exec/exec_cmd \
			make/deps/exec/builtin \
			make/deps/exec/exec_redir \
			make/deps/exec/exec_pipe \
			make/deps/exec/exec_operator \
			make/deps/exec/exec_parenthesis \
			make/deps/exec/exec_separator \

OBJS = $(SRCS:src/%.c=$(OBJDIR)/%.o)
DEPS = $(SRCS:src/%.c=$(DEPDIR)/%.d)

HEADER =	include/minishell.h \
			include/parsing/parsing.h \
			include/exec/exec.h \
			include/exec/builtin.h

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

#For debug
valgrind:
	valgrind --leak-check=yes --show-leak-kinds=all --suppressions=.valgrind_suppress.txt -s ./minishell

valgrind-full:
	valgrind --suppressions=.valgrind_suppress.txt --leak-check=full --track-fds=yes --trace-children=yes --show-leak-kinds=all --track-origins=yes ./minishell

valgrind-log:
	valgrind --leak-check=full --track-origins=yes --suppressions=.valgrind_suppress.txt --log-file=valgrind-out.txt ./minishell

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