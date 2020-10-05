CC     := cc
CFLAGS := -lcurses

SRC := src
OBJ := obj

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SOURCES))

all: ammolite

ammolite: $(OBJECTS) 
	$(CC) $^ $(CFLAGS) -o $@ 

$(OBJ)/%.o: $(SRC)/%.c
	test -d $(OBJ) || mkdir $(OBJ)
	$(CC) $< -c -I$(SRC) $(CFLAGS) -o $@

clean:
	rm $(OBJ)/*.o ammolite
