# Compiler options
CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic -std=c11

# Source files and object files
SRCDIR = src
BINDIR = bin
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = generate

# Libraries
LIBS = -lc

# Build target
all: ${BINDIR}/$(TARGET)

${BINDIR}/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $(LIBS) -o $@ $^

# Object files
%.o: %.c
	$(CC) $(CFLAGS) $(LIBS) -c -o $@ $<

# Clean up
clean:
	rm -f $(OBJS) ${BINDIR}/$(TARGET)