CC = gcc
CFLAGS = -Wall -Wextra -g
SRCDIR = src
BUILDDIR = build
BINDIR = build/bin
CMD_DIR = $(SRCDIR)/cmd

SRCEXT = c
SOURCES = $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CMD_SOURCES = $(shell find $(CMD_DIR) -type f -name *.$(SRCEXT))
CMD_OBJECTS = $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(CMD_SOURCES:.$(SRCEXT)=.o))

EXECUTABLE = $(BINDIR)/treedir

.PHONY: all clean

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) $(CMD_OBJECTS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $^ -o $@

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILDDIR)/cmd/%.o: $(CMD_DIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -r $(BUILDDIR)
