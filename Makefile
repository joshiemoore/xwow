CC=gcc

BLD=xwow.o bg/bg_corners.o bg/bg_fade.o bg/bg_cyber.o

%.o: %.c
	$(CC) -c -o $@ $<

all: $(BLD)
	$(CC) -o xwow *.o bg/*.o -lX11 -lSDL2 -lm

clean:
	rm *.o
	rm bg/*.o
	rm xwow
