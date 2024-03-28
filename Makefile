CC = gcc
CFLAGS = -std=c99 -Wall -Wpedantic

OBJDIR = obj
SRCDIR = src
OUTDIR = target

SOURCES = Board.c

SOURCE_FILES = $(SOURCES:%.c=$(SRCDIR)/%.c)
OBJECT_FILES = $(SOURCES:%.c=$(OBJDIR)/%.o)

build_lib: $(OBJECT_FILES)
	mkdir -p $(OUTDIR)
	ar rcs $(OUTDIR)/chesslib.a $(OBJECT_FILES)

$(OBJECT_FILES): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(OBJDIR)/* $(OUTDIR)/*
