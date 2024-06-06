CC = gcc
CFLAGS = -std=c99 -Wall -Wpedantic -g

OBJDIR = obj
SRCDIR = src
OUTDIR = target

SOURCES = \
	Position.c

SOURCE_FILES = $(SOURCES:%.c=$(SRCDIR)/%.c)
OBJECT_FILES = $(SOURCES:%.c=$(OBJDIR)/%.o)

build_lib: $(OBJECT_FILES)
	mkdir -p $(OUTDIR)
	ar rcs $(OUTDIR)/chesslib.a $(OBJECT_FILES)

debug: $(OBJECT_FILES)
	mkdir -p $(OUTDIR)
	$(CC) -c $(CFLAGS) $(SRCDIR)/main.c -o $(OBJDIR)/main.o
	$(CC) $(CFLAGS) $(OBJECT_FILES) obj/main.o -o $(OUTDIR)/chess

$(OBJECT_FILES): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm $(OBJDIR)/* $(OUTDIR)/*
