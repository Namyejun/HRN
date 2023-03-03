EXEC = hrrn
CC = gcc
CFLAGS = -Wall

$(EXEC): hrrn.o
	$(CC) -g -o ../hrrn hrrn.o -L../lib -l_hrrn_func

%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@ -I../include

clean: 
	rm hrrn.o ../hrrn
