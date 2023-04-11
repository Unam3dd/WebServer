NAME = client
SRCS = $(shell find . -iname "*.cpp" -print)
OBJS = $(SRCS:.cpp=.o)
CC = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I../inc -I../inc/libsocket

all: $(NAME)

%.o: %.cpp
	$(CC) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CXXFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

.PHONY: all clean fclean re
