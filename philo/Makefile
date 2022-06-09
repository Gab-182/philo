# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gabdoush <gabdoush@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/14 19:41:47 by gabdoush          #+#    #+#              #
#    Updated: 2022/06/06 04:43:35 by gabdoush         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

FILES = philo_utils_libft.c\
		parse_arguments.c\
		philo_routine.c\
		philo_utils.c\
		eating.c\
		philo.c\
		main.c

HEADERS = ./philo.h

OBJ = $(FILES:.c=.o)

FLAGS = -Wall -Wextra -Werror

CC = gcc

R = \033[1;31m
G = \033[1;32m
Y = \033[1;33m
B = \033[1;34m
RESET = \033[0m

all: $(NAME)
$(NAME): $(OBJ)
	@echo "$(Y)——————————————————————————————————————————————————————————————$(RESET)"
	@echo "$(G)【OK】$(RESET) $(B)Compiling with the flags....$(RESET)"

	@$(CC) -pthread -g $(FILES) $(FLAGS) -o philo

	@echo "$(G)【OK】❮philo❯ CREATED$(RESET)"
	@echo "$(Y)——————————————————————————————————————————————————————————————$(RESET)"

clean:
	@echo "$(Y)——————————————————————————————————————————————————————————————$(RESET)"
	@rm -rf $(OBJ)
	@echo "\033c"
	@echo "$(G)【OK】 $(RESET)        $(R)❮philo❯ objects have been DELETED$(RESET)"
	@echo "$(Y)——————————————————————————————————————————————————————————————$(RESET)"

fclean: clean
	@rm -rf philo
	@echo "\033c"
	@echo "$(G)【OK】 $(RESET)        $(R)❮philo excutable❯ DELETED$(RESET)"
	@echo "$(Y)——————————————————————————————————————————————————————————————$(RESET)"

re: fclean all

.PHONY: all clean fclean re