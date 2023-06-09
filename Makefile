##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## This is just a Makefile but v2
##

BINARY = dante
GENERATOR_DIR = generator
SOLVER_DIR = solver

LIBRARY = libmy.a
SHARED_DIR = shared
LIBRARY_DIR = $(SHARED_DIR)/library

CC = gcc

C_FLAGS = -Wall -Wextra -g $(foreach F,$(INCLUDE),-I$(F))

RST = \033[0m
CYAN = \033[36m
PINK = \033[37;1m
GREEN = \033[0;32m
CORAL = \033[0;31m
ORANGE = \033[0;33m
MAGENTA = \033[0;35m

L_SOURCES = $(wildcard $(LIBRARY_DIR)/*.c)
L_OBJECTS = $(patsubst %.c,%.o,$(L_SOURCES))

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
    ECHO_OPTS :=
else ifeq ($(UNAME_S), Linux)
    ECHO_OPTS := -e
else
    $(error Unsupported operating system: $(UNAME_S))
endif

all: $(SHARED_DIR)/$(LIBRARY) $(BINARY)

$(SHARED_DIR)/$(LIBRARY): $(L_OBJECTS)
	@echo $(ECHO_OPTS) "- $(CYAN)Building library \
	$(ORANGE)$(LIBRARY) $(CYAN)archive$(RST)"
	@ar rc $@ $^
	@rm -rf $(L_OBJECTS)

$(SHARED_DIR)/%.o: $(SHARED_DIR)/%.c
	@$(CC) $(C_FLAGS) -c -o $@ $<;

%:
	@echo "- $(MAGENTA)Running recipe $(GREEN)$*$(RST)"
	@$(MAKE) -C $(GENERATOR_DIR) $*
	@$(MAKE) -C $(SOLVER_DIR) $*

re: fclean all

.PHONY: all re
