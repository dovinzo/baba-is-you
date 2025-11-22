.PHONY: all clean

CPP = g++ --std=c++11 -Wall -Iinclude

all: prog

prog: obj/main.o obj/Model.o obj/view.o
	$(CPP) -o prog obj/main.o obj/Model.o obj/view.o -lsfml-graphics -lsfml-window -lsfml-system

obj/main.o: src/main.cpp include/Model.hpp include/ObjectType.hpp include/IReadOnlyModel.hpp
	$(CPP) -c src/main.cpp -o obj/main.o

obj/Model.o: src/Model.cpp include/Model.hpp include/ObjectType.hpp include/IReadOnlyModel.hpp include/ISubject.hpp
	$(CPP) -c src/Model.cpp -o obj/Model.o

obj/view.o: src/view.cpp include/view.hpp include/IReadOnlyModel.hpp include/IObserver.hpp
	$(CPP) -c src/view.cpp -o obj/view.o

clean:
	rm obj/*.o
