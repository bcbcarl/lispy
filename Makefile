CFLAGS = -std=c11 -Wall
LFLAGS = -lm

SRC_DIR = $(CURDIR)/src
TEST_DIR = $(CURDIR)/tests
DIST_DIR = $(CURDIR)/bin

SRC_MAIN = $(SRC_DIR)/main.c
SRCS = $(SRC_DIR)/lispy.c $(SRC_DIR)/mpc.c
TESTS = $(TEST_DIR)/lispy.c $(TEST_DIR)/assert_float.c
DIST = $(DIST_DIR)/lispy

TAGS = GPATH GRTAGS GSYMS GTAGS TAGS

OS := $(shell uname)
GTAGS = $(shell command -v gtags || { echo "gtags not found." >&2; exit 1; })

RM := rm -f
MKDIR := mkdir -p

ifneq ($(OS), Windows_NT)
	LFLAGS += -lreadline
endif

.PHONY: all
all: build

.PHONY: build
build: $(SRC_MAIN) $(SRCS) $(GTAGS)
	@$(GTAGS) .
	@$(MKDIR) $(DIST_DIR)
	@$(CC) $(CFLAGS) $(SRC_MAIN) $(SRCS) $(LFLAGS) -o $(DIST)

.PHONY: test
test: $(SRCS) $(TESTS)
	@$(MKDIR) $(DIST_DIR)
	@$(CC) $(CFLAGS) $(SRCS) $(TESTS) $(LFLAGS) -lcmocka -o $(DIST)_test
	@$(DIST)_test

.PHONY: distclean
distclean: clean
	@$(RM) $(TAGS)

.PHONY: clean
clean:
	@$(RM) -r $(DIST_DIR)
