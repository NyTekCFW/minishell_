# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lchiva <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/21 01:07:40 by lchiva            #+#    #+#              #
#    Updated: 2024/06/21 01:07:40 by lchiva           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


.PHONY: clean fclean norme compilation noflags

NAME = minishell
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)libft.a
TOKEN_DIR = token/
PARSING_DIR = parsing/
EXEC_DIR = exec/
BUILTINS_DIR = builtins/

CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = /bin/rm -f

HDR = $(LIBFT_DIR)libft.h minishell.h $(TOKEN_DIR)token.h $(PARSING_DIR)parsing.h error.h
SRC = minishell.c ft_signals.c ft_clean_ms.c $(addprefix $(TOKEN_DIR), $(TOKEN_SRC)) $(addprefix $(PARSING_DIR), $(PARSING_SRC)) $(addprefix $(EXEC_DIR), $(EXEC_SRC)) $(addprefix $(BUILTINS_DIR), $(BUILTINS_SRC))
TOKEN_SRC = ft_tokenization.c ft_args.c ft_meta.c ft_quotes.c token_lst.c
PARSING_SRC = ft_parse.c ft_expand_var.c ft_expand_var_utils.c ft_clear_quotes.c cmd_lst.c ft_free_array.c io_lst.c ft_create_cmd.c
EXEC_SRC = pipes.c handle_cmd.c get_path.c redirections.c ft_heredoc.c
BUILTINS_SRC = ft_cd.c ft_echo.c ft_env_lst.c ft_env_utils.c ft_env.c ft_exit.c ft_export.c ft_lst_to_char.c ft_pwd.c ft_unset.c
OBJS = $(SRC:.c=.o)

BLACK = \033[30m
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
WHITE = \033[37m
NC = \033[0m

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(LIBFT) $(OBJS)
	@echo "$(RED)Compilation in progress...$(NC)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) -lreadline
	@echo "$(GREEN)Compilation complete !$(NC)"

all: $(NAME)

$(LIBFT):
	@echo "$(YELLOW)Creating libft...$(NC)"
	@make -s -C $(LIBFT_DIR) all

clean:
	@echo "$(YELLOW)Cleaning object files...$(NC)"
	@make -s -C $(LIBFT_DIR) clean
	@$(RM) $(OBJS)
	@echo "$(GREEN)Cleaning complete !$(NC)"

fclean: clean
	@echo "$(YELLOW)Cleaning...$(NC)"
	@make -s -C $(LIBFT_DIR) fclean
	@$(RM) $(NAME)
	@echo "$(GREEN)Cleaning complete !$(NC)"

re: fclean all

norme:
	@echo "$(YELLOW)Checking Norme...$(NC)"
	@norminette $(SRC) $(HDR)
	@echo "$(GREEN)Checking complete !$(NC)"

compilation: $(LIBFT)
	@$(CC) $(CFLAGS) -g -o $(NAME) $(SRC) $(LIBFT) -lreadline

noflags: $(LIBFT)
	@$(CC) -g -o $(NAME) $(SRC) $(LIBFT) -lreadline
