CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = main

.PHONY: all run clean

all: $(TARGET) run clean

$(TARGET): src/main.c
	$(CC) $(CFLAGS) -o $@ $<

run: $(TARGET)
	./$(TARGET)

clean:
	@rm -f $(TARGET)
