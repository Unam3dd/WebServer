###################################
#
#		WebServer Project
#
###################################

AUTHORS = Sam0verfl0w, Clinche
NAME = webserv
WEBSERVER_VERSION = 0.0.1
DIST = release

###################################
#
#			Compiler Information
#
###################################

CC = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I.
VERSION = $(shell $(CC) --version | head -n 1)

###################################
#
#			Color
#
###################################

GREEN 	= \033[38;5;82m
RED   	= \033[38;5;196m
YELLOW 	= \033[38;5;226m
ORANGE	= \033[38;5;202m
PURPLE	= \033[38;5;207m
LBLUE	= \033[38;5;45m
BLUE	= \033[38;5;26m
DGREY	= \033[90m
RESET 	= \033[00m

###################################
#
#		Percentage
#
###################################

NUM_CF	= $(shell ls -lR src/ | grep -F .cpp | wc -l)
PERC	= 0
cnt		= 2


###################################
#
#		Virtual Path
#
###################################

OBJDIR = obj
vpath %.cpp src
vpath %.hpp inc

###################################
#
#		CPP Sources Files
#
###################################

SRC_MAIN = main.cpp

SRCS = $(SRC_MAIN)
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))

ifdef DEBUG
	CXXFLAGS += -g
	DIST = debug
endif

###################################
#
#			BANNER
#
###################################

define banner

$(LBLUE)
	_ _ _ ____ ___  ____ ____ ____ _  _ ____ ____ 
	| | | |___ |__] [__  |___ |__/ |  | |___ |__/ 
	|_|_| |___ |__] ___] |___ |  \  \/  |___ |  \ 
                                             
											 
		Version		: $(GREEN)$(WEBSERVER_VERSION)$(LBLUE)
		CC Version	: $(GREEN)$(VERSION)$(RESET)




$(RESET)
endef
export banner


###################################
#
#			RULES		
#
###################################

all: BANNER $(NAME) $(eval SHELL:=/bin/zsh)

BANNER:
	@printf "$$banner"

.ONESHELL:
$(OBJDIR)/%.o: %.cpp
	@echo -n '['
	@i=2
	@while [ "$$i" -le $(cnt) ]
	@do
	@	echo -n '='
	@	((i++))
	@done
	@echo -n '>'
	@i=$(cnt)
	@while [ "$$i" -le $(NUM_CF) ]
	@do
	@	echo -n ' '
	@done
	@echo -n ']'
	@echo -n " ($(PERC)%)"
	@$(CC) $(CXXFLAGS) -c $< -o $@
	@$(eval PERC=$(shell echo "$(cnt)/$(NUM_CF)*100" | bc -l | tr '.' '\n' | head -n 1))
	@$(eval cnt=$(shell echo $$(($(cnt)+1))))

$(NAME): $(OBJDIR) $(OBJS)
	@printf "\n[+] WebServer Created !"
	@mkdir -p $(DIST)
	@$(CC) $(CXXFLAGS) $(OBJS) -o $(DIST)/$(NAME)

$(OBJDIR):
	@mkdir -p $(sort $(addprefix $(OBJDIR)/, $(dir $(SRCS))))

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(NAME)
	@rm -rf debug release

re: fclean all

.PHONY: all clean fclean re
