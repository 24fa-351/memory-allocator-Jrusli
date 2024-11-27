CC = gcc
CFLAGS = -Wall -g
TARGET = test
OBJS = test.o memory.o

all: $(TARGET)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

test.o: test.c memory.h
	$(CC) $(CFLAGS) -c test.c

memory.o: memory.c memory.h
	$(CC) $(CFLAGS) -c memory.c

clean:
	rm -f *.o $(TARGET)
