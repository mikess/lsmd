CFLAGS ?= -ansi -O2 -fomit-frame-pointer
USRSBIN	= svmanage

all:	$(USRSBIN)

svmanage: svmanage.c lsmd.h
	$(CC) $(CFLAGS) svmanage.c -o svmanage

clean:
	rm -f $(USRSBIN)
