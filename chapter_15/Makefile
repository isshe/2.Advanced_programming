CC = gcc 
CFLAGS = -O2 -Wall -g 
INC = -I../include 
LIB = -lpthread 
SRC = ../lib/*.c 
ADDSRC = ../chapter_3/p68_set_clr_fl.c 

all:
	make p432 
	make p433 
	make p434 
	make p436 
	make p437 
	make p440 
	make p441 
	make p442 
	make p443 
	make p444 
	make p462 
	make p464 
	make p469 


p432:
	$(CC) $(CFLAGS) $(INC) $(SRC) ./p432_pipe.c -o p432.out $(LIB)

p433:
	$(CC) $(CFLAGS) $(INC) $(SRC) ./p433_pager_program_more.c -o p433.out $(LIB)


p434:
	$(CC) -c ./p434_pipe_tellwait.c $(INC) $(SRC)


p436:
	$(CC) $(CFLAGS) $(INC) $(SRC) ./p436_pager_program_popen.c -o p436.out $(LIB)


p437:
	$(CC) -c ./p437_popen_pclose.c $(INC) $(SRC)


p440:
	$(CC) $(CFLAGS) $(INC) $(SRC) ./p440_to_lower.c -o p440.out $(LIB)


p441:
	$(CC) $(CFLAGS) $(INC) $(SRC) ./p441_read_command.c -o p441.out $(LIB)

p442:
	$(CC) $(CFLAGS) $(INC) $(SRC) ./p442_add.c -o p442.out $(LIB)

p443:
	$(CC) $(CFLAGS) $(INC) $(SRC) ./p443_sig_pipe_coprocess.c -o p443.out $(LIB)

p444:
	$(CC) $(CFLAGS) $(INC) $(SRC) ./p444_add_stdio.c -o p444.out $(LIB)

p462:
	$(CC) $(CFLAGS) $(INC) $(SRC) ./p462_tshm.c -o p462.out $(LIB)

p464:
	$(CC) $(CFLAGS) $(INC) $(SRC) ./p464_devzero_mmap_IO.c -o p464.out $(LIB)

p469:
	$(CC) -c ./p469_sem_lock.c $(INC) $(SRC)


.PHONE:clean 
clean:
	rm -f *.out 
	rm -f *.o
