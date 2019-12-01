BIN  := cimulink
SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

CFLAGS := -g -Wall -std=gnu99

$(BIN): $(OBJS)
	$(CC) -o $@ $(OBJS)

%.o : %.c $(wildcard *.h)
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm *.o $(BIN)