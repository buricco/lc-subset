SUBDIRS= banner basename cat df dirname dmesg echo env hostname kill \
	killall5 line link logname mkdir mount news nice nologin random \
	readlink realpath renice rmdir sleep sum sync tty uname unlink uptime \
	yes

.PHONY:	all clean

all clean:
	for x in $(SUBDIRS); do \
		$(MAKE) -C $$x -f Makefile $@;	\
	done
