

SRCS := $(wildcard *.c)
OBJS := $(SRCS:.c=.o)

CFLAGS := -g

booler: booler.o parse.o
	gcc $(CFLAGS) -o $@ $^

booler.o: booler.c parse.h
	gcc $(CFLAGS) -c -o $@ $<

parse.o: parse.c parse.h
	gcc $(CFLAGS) -c -o $@ $<

clean:
	rm booler *.o
