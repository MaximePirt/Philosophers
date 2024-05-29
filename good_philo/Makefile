# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/18 01:25:54 by mpierrot          #+#    #+#              #
#    Updated: 2024/05/29 00:44:19 by mpierrot         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_F	= 	init.c thread.c lib_func_recode.c main.c parsing.c
SRC_D	= src/
OBJ_D = objs
OBJ_F = $(SRC_F:%.c=$(OBJ_D)/%.o)
CC = cc
CFLAGS = -g -Wall -Wextra -Werror
RM = rm -rf
NAME = philo


DEFCOLOR	= \033[0;39m
CYAN		= \033[1;96m
PURPLE		= \033[0;95m
YELLOW		= \033[0;93m
RED			= \033[0;91m

all: $(NAME)


$(NAME): $(OBJ_F) 
	@$(CC) $(CFLAGS) $(OBJ_F) -o $(NAME)
	@echo "$(CYAN)philo has been compiled successfully$(DEFCOLOR)"

$(OBJ_D)/%.o: %.c
	@mkdir -p $(OBJ_D)
	@echo "$(YELLOW)Compiling $<$(DEFCOLOR)"
	@$(CC) $(CFLAGS) -c $< -o $@

	
clean:
	@$(RM) objs
	@echo "$(PURPLE)philo object files cleaned !!$(DEFCOLOR)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)philo executable has been destroy$(DEFCOLOR)"

re: fclean all

.PHONY: all clean fclean re bonus