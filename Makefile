CFLAGS = -std=c11 -Wall
LFLAGS = -lm

SRCS = evaluation.c mpc.c
DIST_DIR = $(CURDIR)/bin
DIST = $(DIST_DIR)/evaluation
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
