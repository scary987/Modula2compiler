.PHONY: clean

OBJECTS := main.o buffer.o tokens.o scanner.o diagnosis.o symboltable.o

all: moco

main.o: main.c buffer.h tokens.h

buffer.o: buffer.c buffer.h

tokens.o: tokens.c tokens.h

moco: $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $@

clean:
	$(RM) $(OBJECTS) moco
