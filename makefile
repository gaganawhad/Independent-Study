project: GNFA.o regex.o multiset.o stack.o alphabet.o main.o
	g++ GNFA.o multiset.o regex.o stack.o alphabet.o main.o -o project
main.o: main.cpp GNFA.h
	g++ -c main.cpp
GNFA.o: GNFA.h GNFA.cpp multiset.h 
	g++ -c GNFA.cpp
multiset.o: multiset.h multiset.cpp
	g++ -c multiset.cpp
regex.o: regex.h regex.cpp stack.h
	g++ -c regex.cpp
alphabet.o: alphabet.h alphabet.cpp
	g++ -c alphabet.cpp
stack.o: stack.h stack.cpp
	g++ -c stack.cpp
clean:
	rm main.o GNFA.o regex.o alphabet.o stack.o multiset.o
