CC = gcc 
CFLAGS = -O2 -Wall -g 
INC = -I../include 
LIB = -lpthread 
SCR = ../lib/*.c 

all:
	make p310 
	make p312 
	make p313 
	make p316 
	make p322 
	make p323 
	make p328 
	make p330 
	make p334 
	make p337 

p310:
	$(CC) $(CFLAGS) $(INC) $(SCR) p310_print_thread_ID.c -o p310.out $(LIB)

p312:
	$(CC) $(CFLAGS) $(INC) $(SCR) p312_get_exit_code.c -o p312.out $(LIB)

p313:
	$(CC) $(CFLAGS) $(INC) $(SCR) p313_pthread_exit_error_use.c -o p313.out $(LIB)

p316:
	$(CC) $(CFLAGS) $(INC) $(SCR) p316_thread_cleanup_func.c -o p316.out $(LIB)

p322:
	$(CC) -c  p322_use_mutex.c 

p323:
	$(CC) -c  p323_use_2_mutex_1.c 


p328:
	$(CC) $(CFLAGS) $(INC) $(SCR) p328_pthread_mutex_timelock.c -o p328.out $(LIB)

p330:
	$(CC) -c  p330_use_rwlock.c 

p334:
	$(CC) -c  p334_use_cond.c 

p337:
	$(CC) $(CFLAGS) $(INC) $(SCR) p337_use_pthread_barrier.c -o p337.out $(LIB)


.PHONE:clean 
clean:
	rm -f *.out 
	rm -f *.o
