CC      = g++
FLAGS  = -Wall -Wextra -g

all: submission

#HW1: OShay_HW1.o 
#	$(CC) $(FLAGS) OShay_HW1.o -o HW1

submission: main.cpp Graph.h Graph.cpp
	$(CC) $(FLAGS) main.cpp Graph.cpp -o submission
#OShay_HW1.o:	OShay_HW1.cpp Card.h Card.cpp
#	$(CC) $(FLAGS) OShay_HW1.cpp -o OShay_HW1.o

clean:
	rm -f submission
