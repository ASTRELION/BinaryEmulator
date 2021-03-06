CC = gcc
CFLAGS = -Werror

BIN = main
SRCS = main.c machine.c instructionUtil.c

OBJS = $(SRCS:.c=.o)

all: $(BIN)

$(BIN): $(OBJS)
	$(CC) $(CFLAGS) -o $(BIN) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) -c $<  -o $@ 

clean:
	rm -f *.o vgcore.* main 