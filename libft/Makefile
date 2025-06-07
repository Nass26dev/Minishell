# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nass <nass@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/18 13:53:26 by eelissal          #+#    #+#              #
#    Updated: 2025/06/07 16:17:40 by nass             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Folders

BIN		:= bin
INC		:= includes
SRC		:= src

# Properties

NAME	= libft.a

# Commands

CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror
RM			:= rm -rf
INCLUDES	:= -I$(INC)


# Sources

HEADERS	:= $(addprefix $(INC)/,	\
				libft.h \
				)

SRCS := ft_atoi.c \
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

OBJS		:= $(addprefix $(BIN)/, $(SRCS:.c=.o))

all:		$(NAME)

$(BIN)/%.o:	$(SRC)/%.c $(HEADERS) Makefile
			@mkdir -p $(dir $@);
			@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
			@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME):	$(OBJS)
			@ar rcs $@ $?
			@ar rcs $@ $?

clean:
			@$(RM) $(OBJS)
			@$(RM) $(OBJS)

fclean:		clean
			@$(RM) $(NAME)
			@if [ -d bin ]; then find bin -type d -empty -delete; fi

re:			fclean all

.PHONY:		all clean fclean re