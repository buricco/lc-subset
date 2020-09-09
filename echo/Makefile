all:	echo

echo:	echo.o
	$(CC) -o echo echo.o

echo.o:	echo.c
	$(CC) -c -o echo.o echo.c

clean:
	rm -f echo echo.o

install:
	install -d -m 755 echo ${DESTDIR}/bin
