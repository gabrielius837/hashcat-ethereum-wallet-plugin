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
LIBS = -L./lib -lsecp256k1 -lXKCP

# Build target
all: ${BINDIR}/$(TARGET)

${BINDIR}/$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) 

# Object files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Clean up
clean:
	rm -f $(OBJS) ${BINDIR}/$(TARGET)
