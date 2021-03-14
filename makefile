SOURCE = ./source/
SOURCES = ./source/*
FLAGS = -std=c++17 -pthread -O2
OBJECTIVES = ./build/trits.o

default: main

main: $(SOURCES)
	$(MAKE) -C ./build
	g++ $(FLAGS) $(OBJECTIVES) $(SOURCE)/main.cpp -o ./main

clean:
	rm -f ./build/*.o ./main ./test

tests: $(SOURCES)
	$(MAKE) -C ./build
	g++ $(FLAGS) $(OBJECTIVES) tests.cpp -o ./test