# Compiler options
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I/usr/include/wolfssl

# Source files and object files
SRCDIR = src
BINDIR = bin
SRCS = $(wildcard $(SRCDIR)/*.c)
OBJS = $(SRCS:.c=.o)

# Executable name
TARGET = generate

# Libraries
LIBS = -lwolfssl

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