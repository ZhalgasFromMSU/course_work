SOURCE = ./source
FLAGS = -std=c++17 -pthread -O2
OBJECTIVES = ./build/trits.o

default: main

main: $(SOURCE)/main.cpp $(SOURCE)/*
	$(MAKE) -C ./build
	g++ $(FLAGS) $(OBJECTIVES) $(SOURCE)/main.cpp -o ./main

clean:
	rm -f ./build/*.o ./main

tests: $(SOURCE)/main.cpp $(SOURCE)
	$(MAKE) -C ./build
	g++ $(FLAGS) $(OBJECTIVES) tests.cpp -o ./test