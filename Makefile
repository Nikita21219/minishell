NAME = minishell
CC = cc
OBJDIR = ./objs
CFLAGS = -Wall -Wextra -Werror
HEADER = minishell.h
SRC = $(wildcard *.c)
OBJ = $(addprefix $(OBJDIR)/,$(notdir $(SRC:.c=.o)))
LIBFT_DIR = libft/

all:    $(NAME)

$(OBJDIR)/%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME):    $(OBJDIR) $(OBJ)
	make -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(LIBFT_DIR)/libft.a -I $(HEADER) $(OBJ) -lreadline

$(OBJDIR):
	@if [ ! -d $(OBJDIR) ] ; then echo "creating $(OBJDIR)" ; mkdir $(OBJDIR); fi

clean:
	@if [ -d $(OBJDIR) ] ; then echo "deleting $(OBJDIR)" ; rm -r $(OBJDIR); fi
	make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
