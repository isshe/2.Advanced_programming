CC = gcc 
CFLAGS = -O2 -Wall -g 
INC = -I../include 
LIB = -lpthread 
SRC = ../lib/*.c 
ADDSRC = ../chapter_3/p68_set_clr_fl.c 

all:
	make p389 
	make p394_lock_reg 
	make p394_lock_test 
	make p395 
	make p398 
	make p401 
	make p425 

p389:
	$(CC) $(CFLAGS) $(INC) $(SRC) $(ADDSRC) p389_noblock_read_write.c $(LIB) -o p389.out

p394_lock_reg:
	$(CC) -c ./p394_lock_reg.c $(INC) $(SRC)

p394_lock_test:
	$(CC) -c ./p394_lock_test.c $(INC) $(SRC)


p395:
	$(CC) $(CFLAGS) $(INC) $(SRC) ./p395_check_lock.c ./p394_lock_reg.c $(LIB) -o p395.out


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
