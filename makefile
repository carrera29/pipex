NAME  	= pipex.a
LIB 	= ar -rcs

SRC		= find_path.c ft_split.c pipex.c utils.c

OBJS 	= $(SRC:.c=.o)

CFLAGS 	= -Wall -Wextra -Werror

$(NAME) : $(OBJS)
	$(LIB) $(NAME) $(OBJS)
	$(NAME)

all : $(NAME)

clean : 
	rm -f $(OBJS) $(OBJS_B)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re