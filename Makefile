.phony: clean


CFLAGS = -Wall -g
TARGETS = moco.o moco

moco: moco.o
	$(CC) $(CFLAGS) -o moco $< 
moco.o: main.c
	$(CC) $(CFLAGS) -c $< -o $@ 
clean: 
	$(RM) $(TARGETS)