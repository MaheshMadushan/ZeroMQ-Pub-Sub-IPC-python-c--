sub : sub.o
		g++ -Wall -g sub.cpp -lzmq -lpthread -o sub
sub.o : sub.cpp
			cc -c sub.cpp -lzmq
clean : 
		rm sub sub.o -f