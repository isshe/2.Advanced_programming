CC = gcc 
CFLAGS = -O2 -Wall -g 
INC = -I../include 
LIB = -lpthread 
SRC = ../lib/*.c 
ADDSRC = ../chapter_3/p68_set_clr_fl.c 

all:
	make p508 
	make p510 
	make p512 

p508:
	$(CC) $(CFLAGS) $(INC) $(SRC) ./p508_unix_socket_poll_XSI_msg.c -o p508.out $(LIB)

p510:
	$(CC) $(CFLAGS) $(INC) $(SRC) ./p509_send_msg_p508.c -o p510.out $(LIB)

p512:
	$(CC) $(CFLAGS) $(INC) $(SRC) ./p512_bind_unix_socket.c -o p512.out $(LIB)


p398:
	$(CC) -c ./p398_lockfile.c $(INC) $(SRC)


p401:
	$(CC) $(CFLAGS) $(INC) $(SRC) ./p401_mandatory.c ./p394_lock_reg.c $(LIB) -o p401.out


p425:
	$(CC) $(CFLAGS) $(INC) $(SRC) ./p425_mmap_copy_file.c $(LIB) -o p425.out


.PHONE:clean 
clean:
	rm -f *.out 
	rm -f *.o
