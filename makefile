# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: clcarre <clcarrer@student.42madrid.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/09 10:34:09 by clcarre           #+#    #+#              #
#    Updated: 2022/08/09 11:58:10 by clcarre          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME  	= pipex.a 
LIB 	= ar -rcs

SRC		= find_path.c split.c pipex.c utils.c

OBJS 	= $(SRC:.c=.o)

CFLAGS 	= -Wall -Wextra -Werror

$(NAME) : $(OBJS)
	$(LIB) $(NAME) $(OBJS)

pipex 	:
	gcc pipex.c pipex.a

all		: $(NAME)

clean 	: 
	rm -f $(OBJS)

fclean 	: clean
	rm -f $(NAME)

re 		: fclean all

.PHONY 	: all clean fclean re