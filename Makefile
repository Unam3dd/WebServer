# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 17:02:32 by stales            #+#    #+#              #
#    Updated: 2023/03/17 20:26:07 by ldournoi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###################################
#
#		WebServer Project
#
###################################

AUTHORS = Sam0verfl0w, Clinche
NAME = webserv
TEST_NAME = tester
WEBSERVER_VERSION = 0.1.3
DIST = bin
INC_GTEST = inc/greatest
CONTRIB_DIR = contrib
TEST_DIR	= tests

###################################
#
#			Compiler Information
#
###################################

CC = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I. -Iinc -Iinc/libsocket 
TESTFLAGS = -I. -Iinc -Iinc/libsocket -std=c++98
VERSION = $(shell $(CC) --version | head -n 1)

###################################
#
#			Color
#
###################################

GREEN 	= \033[32m
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


SRCS = $(shell find src -iname "*.cpp" -print | sed 's/src\///g')
OBJS = $(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))

###################################
#
#		CPP Sources Test Files
#
###################################

TEST_SRCS = $(shell find tests -iname "*.cpp" -print)
TEST_OBJS = $(addprefix $(OBJDIR)/, $(TEST_SRCS:.cpp=.o))
TEST_WSERV_OBJS = $(filter-out obj/main.o, $(OBJS))

ifdef DEBUG
	CXXFLAGS += -g -DDEBUG=1
	DIST = dbg
endif

ifdef FAST
	CXXFLAGS += -Ofast
endif

###################################
#
#			BANNER
#
###################################

define banner

\033[32m
	_ _ _ ____ ___  ____ ____ ____ _  _ ____ ____ 
	| | | |___ |__] [__  |___ |__/ |  | |___ |__/ 
	|_|_| |___ |__] ___] |___ |  \  \/  |___ |  \ 
                                             

			Long Live the Rocket !

$(LBLUE)
		Version		: $(GREEN)$(WEBSERVER_VERSION)$(LBLUE)
		CC Version	: $(GREEN)$(VERSION)$(LBLUE)
		Credits		: $(GREEN)$(AUTHORS)$(RESET)




$(RESET)
endef
export banner


###################################
#
#			RULES		
#
###################################

all: BANNER $(DIST)/$(NAME) $(eval SHELL:=/bin/zsh)

.ONESHELL:
BANNER:
	@clear
	@printf "$$banner"
	@printf "\n[\033[0;32m\xE2\x9C\x94\033[0m] Check C++ Files... at \033[32m$(shell date)\033[00m\n"
	@if test -f $(DIST)/$(NAME)
	@then
	@printf "\n[\033[0;32m\xE2\x9C\x94\033[0m] Project is already Compiled ! to rebuild use make re\033[00m\n\n"
	@else
	@printf "\n[\033[0;32m\xE2\x9C\x94\033[0m] Compiling C++ Files... at \033[32m$(shell date)\033[00m\n\n"
	@fi

.ONESHELL:
$(OBJDIR)/%.o: %.cpp
	@echo -ne '\e[1A\e[1K'
	@echo -n '[ '
	@i=2
	@while [ "$$i" -le $(cnt) ]
	@do
	@if [ $(PERC) -lt "25" ]
	@then
	@echo -ne "\033[31m=\033[00m"
	@elif [ $(PERC) -gt "25" ] && [ $(PERC) -lt "75" ]
	@then
	@echo -ne "\033[33m=\033[00m"
	@else
	@echo -ne "\033[32m=\033[00m"
	@fi
	@	((i++))
	@done
	@echo -n '🚀 '
	@i=$(cnt)
	@while [ "$$i" -le $(NUM_CF) ]
	@do
	@	echo -n ' '
	@	((i++))
	@done
	@echo -n ']'
	@if [ $(PERC) -lt "25" ]
	@then
	@echo -e " (\033[31m$(PERC)%\033[00m) $<...          "
	@elif [ $(PERC) -gt "25" ] && [ $(PERC) -lt "75" ]
	@then
	@echo -e " (\033[33m$(PERC)%\033[00m) $<...          "
	@else
	@echo -e " (\033[32m$(PERC)%\033[00m) $<...          "
	@fi
	@$(CC) $(CXXFLAGS) -c $< -o $@
	@$(eval PERC=$(shell echo "$(cnt)/$(NUM_CF)*100" | bc -l | tr '.' '\n' | head -n 1))
	@$(eval cnt=$(shell echo $$(($(cnt)+1))))

.ONESHELL:
$(DIST)/$(NAME): $(OBJDIR) $(OBJS)
	@printf "\n[\033[0;32m\xE2\x9C\x94\033[0m] WebServer Created at \033[32m$(shell date)\033[00m"
	@printf "\n[\033[0;32m\xE2\x9C\x94\033[0m] Version Build	: \033[32m$(DIST)\033[00m"
	@printf "\n[\033[0;32m\xE2\x9C\x94\033[0m] Version WServer	: \033[32m$(WEBSERVER_VERSION)\033[00m"
	@mkdir -p $(DIST)
	@$(CC) $(CXXFLAGS) $(OBJS) -o $(DIST)/$(NAME)
	@echo -ne "\n[\033[0;32m\xE2\x9C\x94\033[0m] Sha1sum 		: \033[32m"
	@sha1sum $(DIST)/$(NAME) | cut -d ' ' -f1 | tr '\n' ' '
	@echo -ne "\e[00m"
	@echo -en "\n[\033[0;32m\xE2\x9C\x94\033[0m] Md5sum		: \033[32m"
	@md5sum $(DIST)/$(NAME) | cut -d ' ' -f1 | tr '\n' ' '
	@echo -ne "\e[00m"
	@echo -ne "\n[\033[0;32m\xE2\x9C\x94\033[0m] Sha256sum 		: \033[32m"
	@sha256sum $(DIST)/$(NAME) | cut -d ' ' -f1 | tr '\n' ' '
	@echo -ne "\e[00m"

$(OBJDIR):
	@mkdir -p $(sort $(addprefix $(OBJDIR)/, $(dir $(SRCS))))

clean:
	@rm -rf $(OBJDIR)

fclean: clean
	@rm -rf $(DIST)/$(NAME)
	@rm -rf $(DIST)/$(TEST_NAME)
	@rm -rf bin dbg

re: fclean all

.ONESHELL:
$(INC_GTEST) $(CONTRIB_DIR):
	@if ! git --version > /dev/null
	@then
	@echo -e "\033[31m[-] Git is not installed"
	@else
	@echo -e "\033[32m[+] Cloning greatest please wait...\033[00m"
	@git clone https://github.com/silentbicycle/greatest.git greatest
	@mkdir -p inc/greatest
	@cp greatest/greatest.h inc/greatest
	@cp -r greatest/contrib .
	@fi
	@rm -rf greatest

obj/tests/%.o: tests/%.cpp
	@$(CC) $(TESTFLAGS) -Itests -c $< -o $@

$(TEST_DIR): $(OBJDIR)
	@mkdir -p $(OBJDIR)/$(TEST_DIR)

$(TEST_NAME): $(INC_GTEST) $(CONTRIB_DIR) BANNER $(DIST)/$(NAME) $(OBJS) $(TEST_DIR) $(TEST_OBJS)
	@mkdir -p $(DIST)
	@$(CC) $(TESTFLAGS) -Itests $(TEST_WSERV_OBJS) $(TEST_OBJS) -o $(DIST)/$(TEST_NAME)
	@printf "\n[\033[0;32m\xE2\x9C\x94\033[0m] Tester Created at \033[32m$(shell date)\033[00m"
	@printf "\n[\033[0;32m\xE2\x9C\x94\033[0m] Stored at \033[32m$(DIST)/$(TEST_NAME)\033[00m"

unit: $(INC_GTEST) $(CONTRIB_DIR)
	@echo -e "\033[32m\n[\033[0;32m\xE2\x9C\x94\033[0m]  Greatest was moved to project directory !"
	@echo -e "\n[\033[0;32m\xE2\x9C\x94\033[0m] You can use make test to build test executable !\033[00m"

unit_clean:
	@rm -rf greatest

unit_fclean: unit_clean
	@rm -rf inc/greatest
	@rm -rf contrib

run_tests: $(TEST_NAME)
	./$(DIST)/$(TEST_NAME) -v | ./contrib/greenest

.PHONY: all clean fclean re unit unit_clean unit_fclean test
