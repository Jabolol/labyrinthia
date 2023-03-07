##
## EPITECH PROJECT, 2023
## Makefile
## File description:
## This is just a Makefile but v2
##

PARENT = dante
BINARY = generator
TEST_BINARY = tests_run
SOURCES = sources
INCLUDE = include
LIBRARY = ../shared/libmy.a

CC = gcc

C_FLAGS = -Wall -Wextra -g $(foreach F,$(INCLUDE),-I$(F))
COVERAGE = --coverage
TEST_FLAGS = $(COVERAGE) -lcriterion
TESTING_MACRO = -D__DANTE_TEST_MAIN

C_SOURCES = $(foreach C,$(SOURCES),$(wildcard $(C)/*.c))

OBJECTS = $(patsubst %.c,%.o,$(C_SOURCES))

TEST_SOURCES = $(wildcard tests/*.c)
TEST_OBJECTS = $(patsubst %.c,%.o,$(TEST_SOURCES))

CRITERION = $(C_SOURCES:.c=.gcda) $(C_SOURCES:.c=.gcno)
CRITERION += $(TEST_SOURCES:.c=.gcda) $(TEST_SOURCES:.c=.gcno)

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S), Darwin)
    ECHO_OPTS :=
else ifeq ($(UNAME_S), Linux)
    ECHO_OPTS := -e
else
    $(error Unsupported operating system: $(UNAME_S))
endif

RST = \033[0m
CYAN = \033[36m
PINK = \033[37;1m
GREEN = \033[0;32m
CORAL = \033[0;31m
ORANGE = \033[0;33m
MAGENTA = \033[0;35m

$(PARENT): all

all: $(BINARY)

$(BINARY): $(OBJECTS)
	@echo $(ECHO_OPTS) "- $(CYAN)Building $(ORANGE)$(BINARY) $(CYAN)binary$(RST)"
	@$(CC) -o $@ $^ -L../shared -lmy

%.o: %.c
	@echo $(ECHO_OPTS) "- $(MAGENTA)$<$(RST) -> $(GREEN)$@$(RST)"
	@if [ "$(MAKECMDGOALS)" = "tests_run" ]; then \
		$(CC) $(TESTING_MACRO) $(C_FLAGS) -c -o $@ $< $(COVERAGE); \
	else \
		$(CC) $(C_FLAGS) -c -o $@ $<; \
	fi

clean:
	@echo $(ECHO_OPTS) "- $(CORAL)Cleaning objects + deps$(RST)"
	@rm -rf $(OBJECTS) $(DEPS) $(TEST_OBJECTS) $(CRITERION)

fclean:
	@echo $(ECHO_OPTS) "- $(PINK)Cleaning objects + deps + binary + library$(RST)"
	@rm -rf $(BINARY) $(TEST_BINARY) $(OBJECTS) $(DEPS) \
	$(TEST_OBJECTS) $(CRITERION) $(LIBRARY)

re: fclean all

$(TEST_BINARY): $(OBJECTS) $(TEST_OBJECTS) $(LIBRARY)
	@echo $(ECHO_OPTS) "- $(ORANGE)Running tests$(RST)"
	@$(CC) -o $@ $^ $(TEST_FLAGS)
	@./$@
	@rm -rf $(TEST_SOURCES:.c=.gcda) $(TEST_SOURCES:.c=.gcno)

visualize:
	@gcovr --html --output=index.html

.PHONY: all clean fclean re tests_run
