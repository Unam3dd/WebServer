# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stales <stales@student.42angouleme.fr>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/03 17:02:32 by stales            #+#    #+#              #
#    Updated: 2023/05/24 17:41:42 by stales           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###################################
#
#		WebServer Project
#
###################################

AUTHORS					:= Sam0verfl0w, Clinche, Pixailz
NAME					:= webserv
WEBSERVER_VERSION		:= 1.0.0
DIST					:= bin

###################################
#
#			Compiler Information
#
###################################

CC						:= c++
CXXFLAGS				:= -Wall -Wextra -std=c++98 -I. -Iinc -Iinc/libsocket
TESTFLAGS				:= -I. -Iinc -Iinc/libsocket -std=c++98
VERSION					:= $(shell $(CC) --version | head -n 1)

SHELL					:= /bin/bash

###################################
#
#			Color
#
###################################

# define	R						ANSI_ESC "38:2::255:0:0m"
# define	G						ANSI_ESC "38:2::0:255:0m"
# define	B						ANSI_ESC "38:2::0:0:255m"
# define	C						ANSI_ESC "38:2::0:255:255m"
# define	Y						ANSI_ESC "38:2::255:255:0m"
# define	O						ANSI_ESC "38:2::255:165:0m"

ESC						:= \033[
R						:= $(ESC)38:2::255:0:0m
G						:= $(ESC)38:2::0:255:0m
B						:= $(ESC)38:2::0:0:255m
Y						:= $(ESC)38:2::255:255:0m
O						:= $(ESC)38:2::255:165:0m
P						:= $(ESC)38:2::128:0:128m
C						:= $(ESC)38:2::0:255:255m
RST						:= $(ESC)00m
GOTO_COL				:= $(ESC)26G
MOVUP_CLR				:= $(ESC)1A$(ESC)2K

CHECK					:= [$(G)\xE2\x9C\x94$(RST)]

DATE					= $(shell date "+%H:%M:%S %x")

###################################
#
#		Percentage
#
###################################

NUM_CF					:= $(shell ls -lR src/ | grep -F .cpp | wc -l)
PERC					:= 0
cnt						:= 2

###################################
#
#		Virtual Path
#
###################################

OBJDIR					:= obj
vpath %.cpp src
vpath %.hpp inc

###################################
#
#		CPP Sources Files
#
###################################

SRCS					:= $(shell find src -iname "*.cpp" -print | sed 's|src/||g')
OBJS					:= $(addprefix $(OBJDIR)/, $(SRCS:.cpp=.o))

ifeq ($(DEBUG),)
	CXXFLAGS += -Werror
else
	CXXFLAGS += -g3 -DDEBUG=$(DEBUG)
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

$(G)
	_ _ _ ____ ___  ____ ____ ____ _  _ ____ ____
	| | | |___ |__] [__  |___ |__/ |  | |___ |__/
	|_|_| |___ |__] ___] |___ |  \  \/  |___ |  \


			Long Live the Rocket !

$(C)
		Version		: $(G)$(WEBSERVER_VERSION)$(C)
		CC Version	: $(G)$(VERSION)$(C)
		Credits		: $(G)$(AUTHORS)$(RST)





endef
export banner


###################################
#
#			RULES
#
###################################

.SILENT:

all: BANNER $(DIST)/$(NAME)

.ONESHELL:
BANNER:
	clear
	printf "$$banner"
	printf "\n$(CHECK) Check C++ Files... at $(G)$(DATE)$(RST)\n"
	if test -f $(DIST)/$(NAME)
	then
	printf "\n$(CHECK) Project is already Compiled ! to rebuild use make re\n\n"
	else
	printf "\n$(CHECK) Compiling C++ Files... at $(G)$(DATE)$(RST)\n\n"
	fi

.ONESHELL:
$(OBJDIR)/%.o: %.cpp
	printf "%b" "$(MOVUP_CLR)"
	echo -n '[ '
	i=2
	if [ $(PERC) -lt "25" ] ; then
		printf "%b" "$(R)"
	elif [ $(PERC) -ge "25" ] && [ $(PERC) -lt "75" ]; then
		printf "%b" "$(Y)"
	else
		printf "%b" "$(G)"
	fi
	while [ "$$i" -le $(cnt) ]; do
		echo -n "="
		((i++))
	done
	printf "%b" "$(RST)"
	echo -n '🚀 '
	i=$(cnt)
	while [ "$$i" -le $(NUM_CF) ]; do
		echo -n ' '
		((i++))
	done
	echo -n ']'
	if [ $(PERC) -lt "25" ]; then
		printf " %b %s...\n" "($(R)$(PERC)%$(RST))" "$<"
	elif [ $(PERC) -ge "25" ] && [ $(PERC) -lt "75" ]; then
		printf " %b %s...\n" "($(Y)$(PERC)%$(RST))" "$<"
	else
		printf " %b %s...\n" "($(G)$(PERC)%$(RST))" "$<"
	fi
	$(CC) $(CXXFLAGS) -c $< -o $@
	$(eval PERC=$(shell echo "$(cnt)/$(NUM_CF)*100" | bc -l | tr '.' '\n' | head -n 1))
	$(eval cnt=$(shell echo $$(($(cnt)+1))))

.ONESHELL:
$(DIST)/$(NAME): $(OBJDIR) $(OBJS)
	printf "\n$(CHECK) WebServer Created at $(GOTO_COL)$(G)$(DATE)$(RST)\n"
	printf "$(CHECK) Version Build$(GOTO_COL)$(G)$(DIST)$(RST)\n"
	printf "$(CHECK) Version WServer$(GOTO_COL)$(G)$(WEBSERVER_VERSION)$(RST)\n"
	mkdir -p $(DIST)
	$(CC) $(CXXFLAGS) $(OBJS) -o $(DIST)/$(NAME)
	[ "$$?" != "0" ] && return || printf "\x1b[1A"
	printf "\n"
	printf "$(CHECK) Md5sum$(GOTO_COL)$(G)%s$(RST)\n" "$$(md5sum $(DIST)/$(NAME) | cut -d ' ' -f1)"
	printf "$(CHECK) Sha1sum$(GOTO_COL)$(G)%s$(RST)\n" "$$(sha1sum $(DIST)/$(NAME) | cut -d ' ' -f1)"
	printf "$(CHECK) Sha256sum$(GOTO_COL)$(G)%s$(RST)\n" "$$(sha256sum $(DIST)/$(NAME) | cut -d ' ' -f1)"

$(OBJDIR):
	mkdir -p $(sort $(addprefix $(OBJDIR)/, $(dir $(SRCS))))

clean:
	rm -rf $(OBJDIR)

fclean:					clean
	rm -rf $(DIST)/$(NAME)
	rm -rf $(DIST)/$(TEST_NAME)
	rm -rf bin dbg

re:						fclean all

run:					re
ifeq ($(ARG),)
	./$(DIST)/$(NAME) 420>exec.log
else
	./$(DIST)/$(NAME) $(ARG) 420>exec.log
endif

# BOUH C CACA ÇA :/
.ONESHELL:
$(INC_GTEST) $(CONTRIB_DIR):
	if ! git --version > /dev/null
	then
	echo -e "\033[31m[-] Git is not installed"
	else
	echo -e "\033[32m[+] Cloning greatest please wait...\033[00m"
	git clone https://github.com/silentbicycle/greatest.git greatest
	mkdir -p inc/greatest
	cp greatest/greatest.h inc/greatest
	cp -r greatest/contrib .
	fi
	rm -rf greatest

.PHONY: all clean fclean re
