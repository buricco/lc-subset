all:	kill

kill:   kill.o signames.o
	$(CC) -o kill kill.o signames.o

kill.o:	kill.c signames.h
	$(CC) -c -o kill.o kill.c

signames.o:	signames.c signames.h
	$(CC) -c -o signames.o signames.c

clean:
	rm -f kill kill.o signames.o
