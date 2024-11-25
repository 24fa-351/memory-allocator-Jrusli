CC = gcc
CFLAGS = -Wall -g
TARGET = test
OBJS = test.o memory_manager.o

all: $(TARGET)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

test.o: test.c memory_manager.h
	$(CC) $(CFLAGS) -c test.c

memory_manager.o: memory_manager.c memory_manager.h
	$(CC) $(CFLAGS) -c memory_manager.c

clean:
	rm -f *.o $(TARGET)
