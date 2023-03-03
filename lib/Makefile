CC = gcc
LIB = lib_hrrn_func.a
OBJS = hrrn_process.o hrrn_queue.o scheduling_io.o
CFLAGS = -Wall

$(LIB): $(OBJS)
	$(AR) rv $@ $(OBJS)

%.o: %.c
	$(CC) -c $(CFLAGS) -I../include $< -o $@

clean:
	rm -f $(OBJS) $(LIB)
