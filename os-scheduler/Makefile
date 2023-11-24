CC = gcc
CFLAGS = -Wall -Wextra -std=c11

all: scheduler

scheduler: src/main.c src/scheduler.c src/process.c src/queue.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f scheduler