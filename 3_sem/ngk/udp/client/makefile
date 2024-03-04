CC=gcc
SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
EXE=get_measurement

all: $(EXE)

$(EXE): $(OBJS)
	$(CC) -o $@ $^

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXE)