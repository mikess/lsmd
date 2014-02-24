CFLAGS ?= -ansi -O2 -fomit-frame-pointer
USRSBIN	= svmanage

all:	$(USRSBIN)

svmanage: svmanage.c lsmd.h
	$(CC) $(CFLAGS) svmanage.c -o svmanage

svc_start: svc_start.c
	$(CC) $(CFLAGS) svc_start.c -o svc_start

clean:
	rm -f $(USRSBIN)
