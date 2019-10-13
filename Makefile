# Makefile for RingBuffer


ifeq ($(OS),Linux)
	LDFLAGS= -lpthread -ljack
	CPP = g++ --std=c++17
else
	CPP = clang++ --std=c++17
endif

CFLAGS = -Wall

OBJ = ringbuffer.o ringbuffer_main.o


all: ringbuffer


ringbuffer: $(OBJ)
	$(CPP) -o $@ $(CFLAGS) $(OBJ) $(LDFLAGS)

.cpp.o:
	$(CPP) -c $< $(CFLAGS)

clean:
	rm -f *.o
	rm -f `find . -perm /111 -type f`
