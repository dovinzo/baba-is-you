.PHONY: all clean

CPP = g++ --std=c++11 -Wall -Iinclude

all: prog
	./prog

prog: obj/main.o obj/BoardElement.o obj/Board.o obj/Rules.o obj/Model.o obj/View.o obj/Controller.o obj/MenuModel.o obj/MenuView.o obj/MenuController.o obj/App.o obj/Subject.o obj/BoardSnapshot.o obj/BoardHistory.o
	$(CPP) -o prog obj/main.o obj/BoardElement.o obj/Board.o obj/Rules.o obj/Model.o obj/View.o obj/Controller.o obj/MenuModel.o obj/MenuView.o obj/MenuController.o obj/App.o obj/Subject.o obj/BoardSnapshot.o obj/BoardHistory.o -lsfml-graphics -lsfml-window -lsfml-system

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

obj/MenuModel.o: src/MenuModel.cpp include/MenuModel.hpp
	$(CPP) -c src/MenuModel.cpp -o obj/MenuModel.o

obj/MenuView.o: src/MenuView.cpp include/MenuView.hpp
	$(CPP) -c src/MenuView.cpp -o obj/MenuView.o

obj/MenuController.o: src/MenuController.cpp include/MenuController.hpp
	$(CPP) -c src/MenuController.cpp -o obj/MenuController.o

obj/App.o: src/App.cpp include/App.hpp
	$(CPP) -c src/App.cpp -o obj/App.o

obj/Subject.o: src/Subject.cpp include/Subject.hpp
	$(CPP) -c src/Subject.cpp -o obj/Subject.o

obj/BoardSnapshot.o: src/BoardSnapshot.cpp include/BoardSnapshot.hpp
	$(CPP) -c src/BoardSnapshot.cpp -o obj/BoardSnapshot.o

obj/BoardHistory.o: src/BoardHistory.cpp include/BoardHistory.hpp
	$(CPP) -c src/BoardHistory.cpp -o obj/BoardHistory.o

clean:
	rm obj/*.o
