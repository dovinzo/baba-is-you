.PHONY: all clean

CPP = g++ --std=c++11 -Wall -Iinclude

all: prog

prog: obj/main.o obj/Model.o obj/View.o obj/Controller.o obj/Board.o obj/Rules.o obj/Board_elements.o
	$(CPP) -o prog obj/main.o obj/Model.o obj/View.o obj/Controller.o obj/Board.o obj/Rules.o obj/Board_elements.o -lsfml-graphics -lsfml-window -lsfml-system

obj/main.o: src/main.cpp
	$(CPP) -c src/main.cpp -o obj/main.o

obj/Model.o: src/Model.cpp include/Model.hpp include/Board.hpp include/Rules.hpp include/Board_elements.hpp
	$(CPP) -c src/Model.cpp -o obj/Model.o

obj/View.o: src/View.cpp include/View.hpp
	$(CPP) -c src/View.cpp -o obj/View.o

obj/Controller.o: src/Controller.cpp include/Controller.hpp
	$(CPP) -c src/Controller.cpp -o obj/Controller.o

obj/Board.o: src/Board.cpp include/Board.hpp include/Board_elements.hpp
	$(CPP) -c src/Board.cpp -o obj/Board.o

obj/Rules.o: src/Rules.cpp include/Rules.hpp include/Enums.hpp
	$(CPP) -c src/Rules.cpp -o obj/Rules.o

obj/Board_elements.o: src/Board_elements.cpp include/Board_elements.hpp include/Enums.hpp
	$(CPP) -c src/Board_elements.cpp -o obj/Board_elements.o

clean:
	rm obj/*.o
