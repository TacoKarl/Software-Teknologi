CC=gcc
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
EXE=measurement_server

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXE)