CC=gcc
CFLAGS=-Wall
LDFLAGS=-lglfw -lGL
EXEC=furry-adventure
SRC=$(wildcard src/*.c)
OBJ=$(SRC:.c=.o)

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *.o

mrproper: clean
	rm -f $(EXEC)