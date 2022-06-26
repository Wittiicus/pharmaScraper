level=1

assgn2: .FORCE
	gcc -o arschit arschit.c log.c -D_level=$(level) -D_multithread -lpthread
.FORCE:
