CC=gcc

BLD=xwow.o bg/bg_corners.o bg/bg_fade.o bg/bg_cyber.o bg/bg_square.o \
  bg/bg_party.o

%.o: %.c
	$(CC) -c -o $@ $<

all: $(BLD)
	$(CC) -o xwow *.o bg/*.o -lX11 -lSDL2 -lm

install: all
	ln -s $(shell pwd)/xwow /usr/local/bin/xwow

uninstall:
	rm -f /usr/local/bin/xwow

clean:
	rm -f *.o
	rm -f bg/*.o
	rm -f xwow
