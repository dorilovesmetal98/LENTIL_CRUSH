CC      = gcc
RM		= rm -rf
CFLAGS  = -O2 -pedantic -Wall -Wextra

BUILDDIR = build
SOURCEDIR = src
HEADERDIR = header

SOURCES := $(shell find $(SOURCEDIR) -name '*.c')

NAME = lentil_crush

.PHONY: all clean

all: $(NAME)

$(NAME): $(SOURCES)
	$(CC) $(CFLAGS) -I$(HEADERDIR) $(SOURCES) -o $(BUILDDIR)/$(NAME)

clean:
    