# Compiler options
CC = gcc
CFLAGS = -Wall -Wextra -std=c11

# Source files and object files
SRCDIR = src
BINDIR = bin
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = generate

# Build target
all: ${BINDIR}/$(TARGET)

${BINDIR}/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Object files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)