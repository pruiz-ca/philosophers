# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pruiz-ca <pruiz-ca@student.42madrid.com>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/18 21:58:46 by pruiz-ca          #+#    #+#              #
#    Updated: 2021/08/13 20:08:45 by pruiz-ca         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

S			=	src/
I			=	inc/
O			=	obj/

SRCS		=	$Smain.c $Sutils.c $Sactions.c $Slib.c

OBJS		=	$(SRCS:$S%.c=$O%.o)

HEADER		=	-I $I

CC			=	clang

FLAGS		=	-Wall -Wextra -Werror

EXTRA		=	#-fsanitize=address

all:			$(NAME)

$(NAME):		$(OBJS)
				@$(CC) $(FLAGS) $(EXTRA) $(SRCS) $(HEADER) -lpthread -o $(NAME)

$O%.o: 			$S%.c
				@[ -d $(O) ] || mkdir -p $(O)
				@$(CC) $(CFLAGS) -c $< $(HEADER) -o $@

clean:
				@rm -rf $(O)

fclean:			clean
				@rm -f $(NAME)
				@rm -rf $(NAME).dSYM
				@find . -name ".DS_Store" -delete

re:				fclean all

run:			re
				@make clean
				./$(NAME)

norm:
				@norminette $(ls -Rl | grep *.c *.h)

.PHONY:			all clean fclean re run norm
