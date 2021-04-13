CC     := cc
CFLAGS := -O3 -Wall -lcurses

SRC := src

SOURCES := $(wildcard $(SRC)/*.c)
OBJECTS := $(patsubst $(SRC)/%.c, %.o, $(SOURCES))

all: ammolite

ammolite: $(OBJECTS)
	$(CC) $^ $(CFLAGS) -o $@

%.o: $(SRC)/%.c
	$(CC) $< -c -I$(SRC) $(CFLAGS) -o $@

clean:
	rm *.o ammolite
