CC=gcc
CFLAGS=-Wall -g
LDFLAGS=-lglfw -lGL -lGLEW
EXEC=furry-adventure
SRC_FOLDER=src/
OBJ_FOLDER=obj/
SRC=$(wildcard $(SRC_FOLDER)*.c)
OBJ=$(subst $(SRC_FOLDER),$(OBJ_FOLDER),$(SRC:.c=.o))

all: $(OBJ_FOLDER) $(EXEC)

$(OBJ_FOLDER):
	mkdir -p $(OBJ_FOLDER)

$(EXEC): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

.SECONDEXPANSION:
$(OBJ_FOLDER)%.o: $(SRC_FOLDER)%.c $$(wildcard $(SRC_FOLDER)$$*.h)
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_FOLDER)

mrproper: clean
	rm -f $(EXEC)