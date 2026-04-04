# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mfassad <mfassad@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/04/04 07:54:57 by mfassad           #+#    #+#              #
#    Updated: 2026/04/04 09:36:39 by mfassad          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
INCLUDES	= -Iinclude -Ilibft
READLINE	= -lreadline

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

SRC_DIR		= src
PARSER_DIR	= $(SRC_DIR)/parser
OBJ_DIR		= obj

SRC			= \
				$(SRC_DIR)/main.c \
				$(PARSER_DIR)/syntax_quotes.c \
				$(PARSER_DIR)/syntax_operators.c \
				$(PARSER_DIR)/syntax_operators_utils.c \
				$(PARSER_DIR)/lexer_core.c \
				$(PARSER_DIR)/lexer_operators.c \
				$(PARSER_DIR)/lexer_words.c \
				$(PARSER_DIR)/token_utils.c \
				$(PARSER_DIR)/expand_utils.c \
				$(PARSER_DIR)/expand_status.c \
				$(PARSER_DIR)/expand_core.c \
				$(PARSER_DIR)/quote_removal.c \
				$(PARSER_DIR)/parse_pipeline.c \
				$(PARSER_DIR)/parse_command.c \
				$(PARSER_DIR)/parse_redirs.c \
				$(PARSER_DIR)/command_utils.c \
				$(PARSER_DIR)/redir_utils.c \
				$(PARSER_DIR)/parser_entry.c \
				$(PARSER_DIR)/parser_cleanup.c \
				$(PARSER_DIR)/parser_debug.c 

OBJ			= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(READLINE) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@make -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re