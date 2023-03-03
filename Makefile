###################################
#
#		WebServer Project
#
###################################

AUTHORS = Sam0verfl0w, Clinche
NAME = webserv
WEBSERVER_VERSION = 0.0.1
DIST = bin
GTEST_INC = inc/gtest
GMOCK_INC = inc/gmock
GTEST_LIB = lib

###################################
#
#			Compiler Information
#
###################################

CC = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++98 -I. -Iinc -Iinc/libsocket
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

ifdef DEBUG
	CXXFLAGS += -g
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
	@printf "$$banner"
	@printf "\n[\033[0;32m\xE2\x9C\x94\033[0m] Check C++ Files... at \033[32m$(shell date)\033[00m\n"
	@if test -f $(DIST)/$(NAME)
	@then
	@printf "\n[\033[0;32m\xE2\x9C\x94\033[0m] Project is already Compiled ! to rebuild use make re\033[00m\n\n\n"
	@else
	@printf "\n[\033[0;32m\xE2\x9C\x94\033[0m] Compiling C++ Files... at \033[32m$(shell date)\033[00m\n\n\n"
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
	@rm -rf $(NAME)
	@rm -rf bin dbg

re: fclean all

.ONESHELL:
$(GTEST_LIB):
	@if ! git --version > /dev/null
	@then
	@echo -e "\033[31m[-] Git is not installed"
	@else
	@git clone https://github.com/google/googletest gtest
	@cd gtest
	@mkdir -p build
	@cd build
	@cmake -DGTEST_CREATE_SHARED_LIBRARY=1 ..
	@make
	@cp -r lib ../../
	@cp -r ../googletest/include/gtest ../../inc
	@cp -r ../googlemock/include/gmock ../../inc
	@fi
	@cd ../../
	@rm -rf gtest


unit: $(INC_GTEST) $(INC_GMOCK) $(GTEST_LIB)
	@echo "YESS"

unit_clean:
	@rm -rf gtest

unit_fclean: unit_clean
	@rm -rf inc/gtest
	@rm -rf inc/gmock
	@rm -rf lib

.PHONY: all clean fclean re unit unit_clean unit_fclean
