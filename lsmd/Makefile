all: clean svc

svc:
	gcc -o svc_start svc_start.c
	gcc -o svc_path  svc_path.c

lsmd:	
	gcc -o lsmd lsmd.c

clean:
	rm -f svc_start lsmd svc_path


