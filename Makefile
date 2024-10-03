CC=gcc
CFLAGS= -Wall -Wextra -g



TARGET=asst6



SRCS=asst6.c some_heap.c



HDRS = some_heaps.h



OBJS = $(SRCS:.c=.o)



OBJ = $(SRCS:.c=.o)



$(TARGET):$(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)



%.o: %.c $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@



clean: rm-f $(OBJS) $(TARGET)
