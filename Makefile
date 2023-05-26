
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
				exec_utils.c \
				exec_pipes.c \
				exec.c \
				freeing.c \
				lexer.c \
				lexer_linked_list.c \
				lexer_memory.c \
				lexer_utils.c \
				main.c \
				parsing.c \
				token_brackets.c \
				token_envvar.c \
				token_envvar_quotes.c \
				token_pipe.c \
				token_quotes.c \
				token_redir.c

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

leak: CFLAGS += -g
leak: all
	@reset
	valgrind --track-fds=yes --trace-children=yes --leak-check=full --show-leak-kinds=all --suppressions=supp.txt ./$(NAME)

leaks: all
	@reset
	leaks --atExit -- ./$(NAME)

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

#Open the subject
pdf : 
	@open https://cdn.intra.42.fr/pdf/pdf/66948/fr.subject.pdf

# Run norminette
norm :
	@echo "\n$W>>>>>>>>>>>>>>>>>>>>>>>>>> $YNORMINETTE $W<<<<<<<<<<<<<<<<<<<<<<<<<<$Z\n"
	@norminette $(SRCS) $(HEADER) $(LIBFT_DIR)
	@echo "\n$W>>>>>>>>>>>>>>>>>>>>>>>> $YNORMINETTE ✅ $W<<<<<<<<<<<<<<<<<<<<<<<<<<"

# -- Avoid file-target name conflicts -- #
.PHONY : all bonus clean fclean re pdf
