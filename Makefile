CC = gcc
CFLAGS = -Werror

BIN = main
SRCS = main.c

OBJS = $(SRCS:.c=.o)

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<  -o $@ 

clean:
	rm $(BIN); find . -type f -name '*.o' -delete