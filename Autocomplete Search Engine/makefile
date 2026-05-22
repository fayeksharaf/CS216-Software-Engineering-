Project2: Project2.o term.o autocomplete.o
	g++ Project2.o term.o autocomplete.o -o Project2

Project2.o: Project2.cpp
	g++ -c Project2.cpp

term.o: term.cpp term.h
	g++ -c term.cpp

autocomplete.o: autocomplete.cpp autocomplete.h term.h SortingList.h
	g++ -c autocomplete.cpp

clean:
	rm -f *.o Project2
