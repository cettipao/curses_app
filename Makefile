CC = gcc
CCFLAGS = -o output
LDFLAGS = -lmenu -lncurses
SRC = main.c app.c led.c login.c

all: output

output:
	$(CC) $(CCFLAGS) $(SRC) $(LDFLAGS)

clean:
	rm -rf *.o output
