.PHONY: all clean

CPP = g++ --std=c++11 -Wall -Iinclude

all: prog

prog: obj/main.o obj/BoardElement.o obj/Board.o obj/Rules.o obj/Model.o obj/View.o obj/Controller.o
	$(CPP) -o prog obj/main.o obj/BoardElement.o obj/Board.o obj/Rules.o obj/Model.o obj/View.o obj/Controller.o -lsfml-graphics -lsfml-window -lsfml-system

obj/main.o: src/main.cpp include/Enums.hpp include/BoardElement.hpp include/Board.hpp include/Rules.hpp include/Model.hpp include/View.hpp include/Controller.hpp
	$(CPP) -c src/main.cpp -o obj/main.o

obj/BoardElement.o: src/BoardElement.cpp include/Enums.hpp include/BoardElement.hpp include/Board.hpp include/Rules.hpp include/Model.hpp
	$(CPP) -c src/BoardElement.cpp -o obj/BoardElement.o

obj/Board.o: src/Board.cpp include/Enums.hpp include/BoardElement.hpp include/Board.hpp include/Rules.hpp
	$(CPP) -c src/Board.cpp -o obj/Board.o

obj/Rules.o: src/Rules.cpp include/Enums.hpp include/Rules.hpp
	$(CPP) -c src/Rules.cpp -o obj/Rules.o

obj/Model.o: src/Model.cpp include/Enums.hpp include/BoardElement.hpp include/Board.hpp include/Rules.hpp include/Model.hpp
	$(CPP) -c src/Model.cpp -o obj/Model.o

obj/View.o: src/View.cpp include/Enums.hpp include/BoardElement.hpp include/Board.hpp include/Rules.hpp include/Model.hpp include/View.hpp
	$(CPP) -c src/View.cpp -o obj/View.o

obj/Controller.o: src/Controller.cpp include/Enums.hpp include/BoardElement.hpp include/Board.hpp include/Rules.hpp include/Model.hpp include/Controller.hpp
	$(CPP) -c src/Controller.cpp -o obj/Controller.o

clean:
	rm obj/*.o
