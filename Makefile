# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eelissal <eelissal@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/05 10:53:23 by nyousfi           #+#    #+#              #
#    Updated: 2025/07/15 18:50:20 by eelissal         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = minishell

MAKEFLAGS += --no-print-directory
CC = cc
CFLAGS = -Wall -Werror -Wextra -MMD -MP -g3
SRCS =	src/main.c \
		src/parsing/loop.c \
		src/parsing/loop_utils.c \
		src/parsing/input.c \
		src/parsing/utils.c \
		src/parsing/error/error.c \
		src/parsing/error/error_type.c \
		src/parsing/lexer/lexer.c \
		src/parsing/lexer/extract.c \
		src/parsing/lexer/extract_utils.c \
		src/parsing/lexer/extract_utils2.c \
		src/parsing/lexer/extract_quote.c \
		src/parsing/lexer/token.c \
		src/parsing/lexer/token_utils.c \
		src/parsing/parser/parser.c \
		src/parsing/parser/parser_utils.c \
		src/parsing/parser/ast.c \
		src/parsing/expand/expand.c \
		src/parsing/expand/expand_token.c \
		src/parsing/expand/expand_utils.c \
		src/parsing/expand/expand_utils2.c \
		src/parsing/expand/concatenation.c \
		src/parsing/expand/node_is.c \
		src/parsing/expand/is.c \
		src/parsing/expand/redir_value.c \
		src/parsing/expand/cmd.c \
		src/parsing/heredoc.c \
		src/parsing/heredoc_creation.c \
		src/exec/exec.c \
		src/exec/builtin/builtin.c \
		src/exec/builtin/env.c \
		src/exec/builtin/echo.c \
		src/exec/builtin/cd.c \
		src/exec/builtin/pwd.c \
		src/exec/builtin/export.c \
		src/exec/builtin/export_utils.c \
		src/exec/builtin/unset.c \
		src/exec/builtin/exit.c \
		src/exec/builtin/utils_builtin.c \
		src/exec/exec_cmd/exec_cmd.c \
		src/exec/exec_cmd/find_cmd_path.c \
		src/exec/exec_cmd/exec_cmd_utils.c \
		src/exec/exec_redir/exec_redir.c \
		src/exec/exec_pipe/exec_pipe.c \
		src/exec/exec_pipe/exec_pipe_redirs.c \
		src/exec/exec_pipe/exec_pipe_utils.c \
		src/exec/exec_operator/exec_operator.c \
		src/exec/clean_exec.c \
		src/utils.c \
		src/utils2.c \
		src/signals/signal.c \
		src/signals/heredoc_signal.c \
		src/env.c \
		src/vector.c \
		src/clean.c \

MAKEDIR = make
OBJDIR = make/objs
SUBOBJDIR = make/objs/parsing \
			make/objs/exec \
			make/objs/signals \
			make/objs/parsing/error \
			make/objs/parsing/lexer \
			make/objs/parsing/parser \
			make/objs/parsing/expand \
			make/objs/parsing/expand \
			make/objs/exec/builtin \
			make/objs/exec/exec_cmd \
			make/objs/exec/exec_redir \
			make/objs/exec/exec_pipe \
			make/objs/exec/exec_operator \
			make/objs/exec/exec_parenthesis \

DEPDIR = make/deps
SUBDEPDIR = make/deps/parsing \
			make/deps/exec \
			make/deps/signals \
			make/deps/parsing/error \
			make/deps/parsing/lexer \
			make/deps/parsing/parser \
			make/deps/parsing/expand \
			make/deps/exec/exec_cmd \
			make/deps/exec/builtin \
			make/deps/exec/exec_redir \
			make/deps/exec/exec_pipe \
			make/deps/exec/exec_operator \
			make/deps/exec/exec_parenthesis \

OBJS = $(SRCS:src/%.c=$(OBJDIR)/%.o)
DEPS = $(SRCS:src/%.c=$(DEPDIR)/%.d)

HEADER =	include/minishell.h \
			include/parsing/parsing.h \
			include/exec/exec.h \
			include/exec/builtin.h \
			include/vector.h \
			include/env.h \

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_ALL := $(filter-out $(LIBFT), $(shell find $(LIBFT_DIR) -type f))

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

$(NAME): $(LIBFT) $(OBJS) $(LIBFT_ALL)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)
	@$(eval COMPILED := 1)

$(LIBFT): $(LIBFT_ALL)
	@echo "$(MESSAGE_COLOR_YELLOW)Building libft... 🛠️$(MESSAGE_RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(MESSAGE_COLOR_GREEN)libft built! ✅$(MESSAGE_RESET)"

$(OBJDIR)/%.o: src/%.c $(HEADER)
	@echo "$(MESSAGE_COLOR_YELLOW)Compiling $@... 🛠️$(MESSAGE_RESET)"
	@mkdir -p $(OBJDIR) $(DEPDIR) $(SUBOBJDIR) $(SUBDEPDIR)
	@$(CC) $(CFLAGS) -I$(LIBFT_DIR)/includes -Iinclude -Iinclude/parsing -Iinclude/exec -c $< -o $@
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
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all files clean fclean re