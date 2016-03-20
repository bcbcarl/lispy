CFLAGS = -std=c11 -Wall
LFLAGS = -lm

SRC_DIR = $(CURDIR)/src
DIST_DIR = $(CURDIR)/bin

SRCS = $(SRC_DIR)/*.c
DIST = $(DIST_DIR)/lispy

vpath %.c $(SRC_DIR)

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
build: $(SRCS) $(GTAGS)
	@$(GTAGS) .
	@$(MKDIR) $(DIST_DIR)
	@$(CC) $(CFLAGS) $(SRCS) $(LFLAGS) -o $(DIST)

.PHONY: distclean
distclean: clean
	@$(RM) $(TAGS)

.PHONY: clean
clean:
	@$(RM) -r $(DIST_DIR)
