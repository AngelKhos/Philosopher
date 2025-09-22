NAME=philo
# /////////////////////////

CC=cc
CC_FLAGS=-Wall -Wextra -Werror -g #-fsanitize=thread

# /////////////////////////

DIR_OBJS=.objs
DIR_DEPS=.deps

# /////////////////////////

SRCS= main.c utils.c philo.c parsing.c init.c fork_action.c time.c
INCS= philo.h
OBJS=$(SRCS:srcs/%.c=$(DIR_OBJS)/%.o)
DEPS=$(SRCS:srcs/%.c=$(DIR_DEPS)/%.d)

# /////////////////////////

all: compile_start $(NAME) compile_done

compile_start:
	echo "$(GREEN) Compile start ... $(END)"

compile_done:
	echo "$(GREEN) Compiling done $(END)"

$(NAME): $(OBJS) $(DEPS) $(INCS) Makefile
	$(CC) $(CC_FLAGS) $(OBJS) -o $@
	echo "$(BLUE) Your philo is ready $(END)"


$(DIR_OBJS)/%.o: srcs/%.c | $(DIR_OBJS) $(DIR_DEPS) 
	$(CC) $(CC_FLAGS) -MMD -MP -MF $(DIR_DEPS)/$*.d -c -o $@ $<

# /////////////////////////

$(DIR_OBJS):
	mkdir -p $(DIR_OBJS)

$(DIR_DEPS):
	mkdir -p $(DIR_DEPS)

# /////////////////////////

clean:
	echo "$(RED)Removing files... $(END)"
	rm -rf $(DIR_OBJS)
	rm -rf $(DIR_DEPS)

fclean: clean
	echo "$(RED)Removing executable... $(END)"
	rm -rf $(NAME)

re: fclean all

# /////////////////////////

GREEN=\033[0;32m
RED=\033[0;31m
BLUE=\033[0;34m
END=\033[0m

# /////////////////////////

.PHONY: all clean fclean re compile_start compile_done
.SILENT: