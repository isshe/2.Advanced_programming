CC = gcc 
CFLAGS = -O2 -Wall -g 
INC = -I../include 
LIB = -lpthread 
SCR = ../lib/*.c 

all:
	make p343 
	make p349 
	make p356 
	make p357 
	make p360 
	make p366 
	make p368 


p343:
	$(CC) -c  p343_create_detach_thread.c 
	
p349:
	$(CC) $(CFLAGS) $(INC) $(SCR) p349_use_recursive_lock.c p343_create_detach_thread.c -o p349.out $(LIB)
		
p356:
	$(CC) -c  p356_getenv_no_reentrance.c 
			
p357:
	$(CC) -c  p357_getenv_reentrance.c 

p360:
	$(CC) -c  p360_getenv_reentrance2.c 
		
p366:
	$(CC) $(CFLAGS) $(INC) $(SCR) p366_deal_with_syn_signal.c -o p366.out $(LIB)
			
p368:
	$(CC) $(CFLAGS) $(INC) $(SCR) p368_eg_pthread_atfork.c -o p368.out $(LIB)
	
.PHONE:clean 
clean:
	rm -f *.out 
	rm -f *.o
