# Makefile for ringbuffer
#
CPP = g++ --std=c++11
CFLAGS = -Wall
LDFLAGS= -lpthread -ljack


OBJ = ringbuffer.o ringbuffer_main.o


all: ringbuffer


ringbuffer: $(OBJ)
	$(CPP) -o $@ $(CFLAGS) $(OBJ) $(LDFLAGS)

.cpp.o:
	$(CPP) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f `find . -perm /111 -type f`

