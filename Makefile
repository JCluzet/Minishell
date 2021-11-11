#  |  |  ___ \    \  |         |
#  |  |     ) |  |\/ |   _  |  |  /   _ 
# ___ __|  __/   |   |  (   |    <    __/ 
#    _|  _____| _|  _| \__,_| _|\_\ \___|
#                              by jcluzet

################################################################################
#                                     CONFIG                                   #
################################################################################

NAME        := minishell
BIMLX       := OFF
CC          := clang
RM		    := rm -f
CFLAGS      := -lreadline -g3

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS_DIR    := ./
SUB_DIR     := ./
INCS        := -I  includes -Wall -Werror -Wextra
OBJ_DIR 	:=	$(BUILD_DIR)/obj
DIRS		:=	$(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SUB_DIR))
OBJS 	    :=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

SRCS        :=      srcs/environement/env_parsing.c \
					srcs/environement/env_utils.c \
					srcs/memory/allocate_sdata.c \
					srcs/memory/free_arr.c \
					srcs/memory/dealocate_sdata.c \
					srcs/utils/str_utils.c \
					srcs/utils/str_manip.c \
					srcs/utils/str_quote.c \
					srcs/utils/list_utils.c \
					srcs/utils/even_more_str_utils.c \
					srcs/utils/dollars_utils.c \
					srcs/utils/get_next_line.c \
					srcs/utils/more_str_utils.c \
					srcs/utils/env_lst_utils.c \
					srcs/utils/general_utils.c \
					srcs/utils/str_arr_utils.c \
					srcs/utils/str_to_word_arr.c \
					srcs/utils/split_env.c \
					srcs/utils/ft_atoi.c \
					srcs/builtins/exit.c \
					srcs/builtins/unset.c \
					srcs/builtins/env.c \
					srcs/builtins/pwd.c \
					srcs/builtins/export.c \
					srcs/builtins/cd.c \
					srcs/builtins/echo.c \
					srcs/execution/dispatcher.c \
					srcs/execution/execution_redirection.c \
					srcs/execution/fd_stack_manage.c \
					srcs/errors/return_functions.c \
					srcs/parsing/stockredir.c \
					srcs/parsing/replace_dollars.c \
					srcs/parsing/linklist.c \
					srcs/parsing/parse_line.c \
					srcs/parsing/redir.c \
					srcs/parsing/check_cmd_executable.c \
					srcs/parsing/fill_cmds.c \
					srcs/parsing/ft_split_space.c \
					srcs/main/shell_loop.c \
					srcs/main/minishell.c \
					srcs/signal/manage_signal.c \
					srcs/execution/redirection_dispatcher.c \
					srcs/utils/remove_str_from_arr.c \
					srcs/execution/execution.c \
					

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED			:= \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m

$(NAME):	$(OBJS)
			@echo "\033[34mCompilation of $(NAME) ...\033[0m"
			@$(CC) $(CFLAGS) $(INCS) $(SRCS) -o $(NAME)
			@echo "\033[32m$(NAME) created\n\033[0m"

all:		$(NAME)

bonus:		all

clean:
			@ echo "Deleting $(CYAN)philo $(CLR_RMV)objs ..."
			@ $(RM) $(OBJS)
			@ rm -rf $(BUILD_DIR)

fclean:		clean
			@ echo "Deleting $(CYAN)philo $(CLR_RMV)binary ..."
			@ $(RM) $(NAME)

re:			fclean all

$(BUILD_DIR):
			@ echo "Creating $(RED) $(NAME) $(CLR_RMV)..."
			@ mkdir $(NAME) $(DIRS)

$(OBJ_DIR)/%.o:$(SRCS_DIR)/%.c ./incs/philo.h | $(BUILD_DIR)
			@ echo "Compiling $(YELLOW) $< $(CLR_RMV)..."
			@ $(CC) $(CFLAGS) -c $< -o $(NAME) $(INCS)

.PHONY:		all clean fclean re
