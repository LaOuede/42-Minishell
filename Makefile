# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gle-roux <gle-roux@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/07 11:12:58 by csenand           #+#    #+#              #
#    Updated: 2023/05/11 15:48:06 by gle-roux         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# -- Executable's name -- #
NAME		=	minishell

# -- Compilation Flag -- #
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
# CFLAGS	=	-Wall -Wextra -Werror -Wunreachable-code -fsanitize=address -g

# -- Remove -- #
RM			=	rm -rf

# -- SRC Files -- #
SRCS_DIR	=	./src/
SRCS_LST	= 	error_handling.c \
				main.c \
				parsing.c \
				tokenization.c

# -- Readline Library -- #
LIBRLINE 		= readline-8.2
LIBRLINE_DIR	= ./libs/readline/
RLINE			= $(LIBRLINE_DIR)libreadline.a

SRCS		=	$(addprefix $(SRCS_DIR), $(SRCS_LST))

# -- OBJ Files -- #
OBJS_DIR	=	./obj/
OBJS_LST	=	$(patsubst %.c, %.o, $(SRCS_LST))
OBJS		=	$(addprefix $(OBJS_DIR), $(OBJS_LST))

# -- HEADER Files -- #
HEADER_DIR	=	./include/
HEADER_LST	=	minishell.h
HEADER	 	=	$(addprefix $(HEADER_DIR), $(HEADER_LST))

# -- LIBFT Files -- #
LIBFT_DIR	=	./libs/libft/
LIBFT		=	$(LIBFT_DIR)libft.a
LIBFT_H		=	$(LIBFT_DIR)include/libft.h

# -- Colors -- #
RESET		= 	\033[0m
RED			= 	\033[0;31m
GREEN		= 	\033[0;32m
YELLOW		= 	\033[0;33m
BLUE		= 	\033[0;34m
PURPLE		= 	\033[0;35m
CYAN		= 	\033[0;36m
ERASE_LINE 	= 	\033[2K\r

# -- Executable's creation -- #
all : dir readline $(NAME)

# -- Compile library -- #
$(NAME) : $(OBJS)
	@make -C $(LIBFT_DIR)
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(RLINE) -lncurses -o $(NAME)
	@echo "✅ $(GREEN)$(NAME)'s exectuable successfully created.		✅$(RESET)"

# -- Create all files .o (object) from files .c (source code) -- #
$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(HEADER)
	@printf "$(ERASE_LINE)🎛️  $(PURPLE)Compiling $(YELLOW)$(notdir $<)\r$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

run: all
	@./$(NAME)

# -- Create directory for *.o files -- #
dir :
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(LIBRLINE_DIR)

readline :
	@if [ ! -f ./libs/readline/libreadline.a ]; then \
		curl -O https://ftp.gnu.org/gnu/readline/$(LIBRLINE).tar.gz; \
		tar -xf $(LIBRLINE).tar.gz; \
		rm -rf $(LIBRLINE).tar.gz; \
		cd $(LIBRLINE) && bash configure && make; \
		mv ./libreadline.a ../libs/readline; \
		rm -rf ../$(LIBRLINE); \
		echo "\n$(ERASE_LINE)$(RESET)----------------------- $(PURPLE)💩 Sorry for all the crap above 💩 $(RESET)----------------------\n"; \
		echo "$(ERASE_LINE)$(RESET)----------------------- $(PURPLE)Readline $(GREEN)succesfully configured ✅ $(RESET)-----------------------\n$(RESET)"; \
	fi

# -- Removes objects -- #
clean :
	@make -C $(LIBFT_DIR) clean
	@printf "💥 $(RED)Removing $(NAME)'s objects...$(RESET)\t\t\t💥\n"
	@$(RM) $(OBJS_DIR)
	@printf "🗑️  $(CYAN)$(NAME)'s object successfully deleted.$(RESET)\t\t🗑️\n"

# -- Removes objects (with clean) and executable -- #
fclean : clean
	@printf "💥 $(RED)Removing executable(s)...$(RESET)				💥\n"
	@$(RM) $(LIBFT)
	@$(RM) $(LIBRLINE_DIR)
	@$(RM) $(NAME)
	@printf "🗑️  $(CYAN)Executable(s) and archive(s) successfully deleted.$(RESET)	🗑️\n\n"

exe : $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all ./pipex
				
# -- Removes objects and executable then remakes all -- #
re : fclean all

# -- Avoid file-target name conflicts -- #
.PHONY : all bonus clean fclean re
