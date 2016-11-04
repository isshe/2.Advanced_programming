CC = gcc 
CFLAGS = -O2 -Wall -g 
INC = -I../include 
LIB = -lpthread 
SRC = ../lib/*.c 

all:
	make p375 
	make p381 
	make p382 
	make p384 
	make p386 

p375:
	$(CC) -c  p375_init_daemon.c $(INC) $(SRC)
	
p381:
	$(CC) -c  p381_only_run_a_daemon.c $(INC) $(SRC)


p382:
	$(CC) $(CFLAGS) $(INC) $(SRC) p382_daemon_reread_config_file.c p381_only_run_a_daemon.c lockfile.c p375_init_daemon.c -o p382.out $(LIB)

p384:
	$(CC) $(CFLAGS) $(INC) $(SRC) p384__daemon_reread_config_file_2.c p381_only_run_a_daemon.c lockfile.c p375_init_daemon.c -o p384.out $(LIB)

p386:
	$(CC) -c ./p386_set_cloexec.c $(INC) $(SRC)


.PHONE:clean 
clean:
	rm -f *.out 
	rm -f *.o
